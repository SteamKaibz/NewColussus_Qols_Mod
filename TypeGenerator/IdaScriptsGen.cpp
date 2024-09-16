#include "IdaScriptsGen.h"



void IdaScriptsGen::dumpIdaIdc() {

	K_Utils::saveStrToFile("Wolf2_IdaIdc.py", getGeneratedIdcPythonScriptStr());

}


classTypeInfo_t* IdaScriptsGen::ClassTypes(unsigned& out_n, unsigned whichsource) {
	/*if (g_offset_classtypes == -1) {
		g_offset_classtypes = FindClassField("typeInfoGenerated_t", "classes")->offset;
		g_offset_nclasstypes = FindClassField("typeInfoGenerated_t", "numClasses")->offset;
	}*/
	//typeInfo_t* typegen = get_typeinfo_generated(whichsource);
	typeInfo_t* typegen = TypeInfoManager::getTypeInfo_t();


	classTypeInfo_t* classes = typegen->classes;

	out_n = typegen->numClasses;
	return classes;
}


enumTypeInfo_t* IdaScriptsGen::EnumTypes(unsigned& out_n, unsigned whichsource) {
	/*if (g_offset_enums == -1) {
		g_offset_enums = FindClassField("typeInfoGenerated_t", "enums")->offset;
		g_offset_nenums = FindClassField("typeInfoGenerated_t", "numEnums")->offset;
	}*/
	typeInfo_t* typegen = TypeInfoManager::getTypeInfo_t();

	out_n = typegen->numEnums;


	//enumTypeInfo_t* enums = *reinterpret_cast<enumTypeInfo_t**>(typegen + g_offset_enums);

	//out_n = *reinterpret_cast<unsigned*>(typegen + g_offset_nenums);
	return typegen->enums;
}


bool IdaScriptsGen::should_skip_type(std::string_view typenam) {
	/*return std::binary_search(g_idc_skipset, &g_idc_skipset[sizeof(g_idc_skipset) / sizeof(g_idc_skipset[0])], typenam, [](const char* l, const char* r) {
		return strcmp(l, r);
		});*/
	return g_fuckset.find(typenam) != g_fuckset.end();

}

//! i believe this is just remove spaces
std::string IdaScriptsGen::normalize_type_name(std::string_view input) {
	std::string result{};
	result.reserve(input.length());
	for (unsigned i = 0; i < input.length(); ++i) {
		unsigned char c = input[i];
		unsigned cc = c;
		if (cc == ' ') {
			continue;
		}
		result.push_back(cc);
	}
	return result;
}


std::string IdaScriptsGen::getGeneratedIdcPythonScriptStr() {


	for (auto&& skipper : g_idc_skipset) {
		g_fuckset.insert(skipper);

	}

	std::string result{};
	std::set<std::string> our_defined_types{};


	result += "from idc import*\nfrom idaapi import *\nid = -1\nti=tinfo_t()\ntl=get_idati()\n";//"#define UNLOADED_FILE   1\n#include <idc.idc>\nstatic main(void){auto id = -1;";


	for (unsigned iterwhen = 0; iterwhen < 2; ++iterwhen)
	{

		unsigned nclasses;
		classTypeInfo_t* iterclasses = ClassTypes(nclasses, iterwhen);

		logInfo("iterclasses: %p", iterclasses);

		//todo add a log here and return from the func so that we can analyse everything

		//x? comment this this for loop for debug:
		//add the structures
		for (unsigned i = 0; true; ++i) {

			if (!iterclasses[i].name) {
				break;
			}

			std::string_view name_sv = iterclasses[i].name;
			if (should_skip_type(name_sv))
				continue;
			result += "add_struc(-1,\"";
			//UNWIND_CODE",0);
			std::string normalized = normalize_type_name(name_sv);

			result += normalized;
			our_defined_types.insert(std::move(normalized));
			result += "\",0)\n";

		}

	}

	//x? !!!!!!!!!!!!!returning for debug
	//return;


	for (unsigned iterwhen = 0; iterwhen < 2; ++iterwhen) {
		unsigned nenums;


		enumTypeInfo_t* enums = EnumTypes(nenums, iterwhen);

		for (unsigned i = 0; i < nenums; ++i) {
			if (!enums[i].name) {
				continue;
			}
			std::string_view name_sv = enums[i].name;

			if (should_skip_type(name_sv))
				continue;


			result += "id = add_enum(0xFFFFFFFFFFFFFFFF,\"";

			std::string normalized = normalize_type_name(name_sv);
			result += normalized;
			our_defined_types.insert(std::move(normalized));
			result += "\",0x1100000)\n";

			enumTypeInfo_t* currenum = &enums[i];

			auto vals = currenum->values;

			while (vals->name && vals->name[0]) {
				result += "add_enum_member(id,\"";
				result += vals->name;
				result += "\",";
				result += std::to_string(vals->value);
				result += ",0XFFFFFFFFFFFFFFFF)\n";
				++vals;

			}
		}
	}
	for (unsigned iterwhen = 0; iterwhen < 2; ++iterwhen) {
		unsigned nclasses;
		classTypeInfo_t* classes = ClassTypes(nclasses, iterwhen);
		for (unsigned i = 0; true; ++i) {

			if (!classes[i].name) {
				break;
			}
			if (should_skip_type(classes[i].name))
				continue;
			result += "id = get_struc_id(\"";
			std::string normalized_name = normalize_type_name(classes[i].name);

			result += normalized_name;

			result += "\")\n";
			result += "sptr=get_struc(get_struc_id(\"";
			result += normalized_name;
			result += "\"))\n";

			/*auto emit_field = [&result, &our_defined_types](const char* name, size_t offset, size_t size, const char* typ, const char* ops) {
				result += "idc.add_struc_member(id,\"";
				result += name;
				result += "\",	";
				std::string offstr = std::to_string((int)offset);
				result += offstr;

				std::string typ2 = normalize_type_name(typ);*/

			auto emit_field = [&result, &our_defined_types, this](const char* name, size_t offset, size_t size, const char* typ, const char* ops) {
				result += "idc.add_struc_member(id,\"";
				result += name;
				result += "\", ";
				std::string offstr = std::to_string((int)offset);
				result += offstr;

				std::string typ2 = normalize_type_name(typ);  // Now 'this' is accessible


				result += ",0x000400,0XFFFFFFFFFFFFFFFF,";

				result += std::to_string((int)size);

				result += ")\n";

				if (typ && typ[0]) {

					std::string deferred_type_append = "";

					deferred_type_append += "memb=get_member(sptr," + offstr + ")\n";
					deferred_type_append += "ti.get_named_type(tl,\"" + typ2 + "\")\n";


					memset(opsbuffer, 0, sizeof(opsbuffer));

					bool in_array = false;
					unsigned opbuffer_writepos = 0;

					for (unsigned opindex = 0; ops[opindex]; opindex++) {
						unsigned opchar = ops[opindex];

						if (in_array) {
							if (opchar == ']') {
								opsbuffer[opbuffer_writepos] = 0;

								int arrbound = atoi(opsbuffer);

								in_array = false;
								opbuffer_writepos = 0;

								deferred_type_append += "ti.create_array(ti, ";
								deferred_type_append += opsbuffer;
								deferred_type_append += ")\n";

							}
							else {
								if ((opchar >= '0' && opchar <= '9') || opchar == '-') {
									opsbuffer[opbuffer_writepos++] = opchar;
								}
								else {
									//cant parse named constant
									return;
								}
							}
						}
						else {
							if (opchar == '[') {
								in_array = true;
							}
							else {
								if (opchar == '*') {
									deferred_type_append += "ti.create_ptr(ti)\n";
								}
							}
						}
					}

					result += deferred_type_append;
					result += "set_member_tinfo(sptr, memb, 0, ti,SET_MEMTI_MAY_DESTROY|SET_MEMTI_USERTI)\n";
				}



				};


			classTypeInfo_t* currclass = &classes[i];

			if (currclass->superType && currclass->superType[0]) {
				auto found = TypeInfoManager::findClassInfo(currclass->superType);
				if (found) {
					size_t sz = found->size;
					emit_field("base", 0, sz, currclass->superType, "");
				}
			}

			classVariableInfo_t* vars = currclass->variables;
			if (vars) {
				while (vars->name && vars->name[0]) {
					if (vars->size != -1) {

						const char* typ_ptr = vars->type;




						emit_field(vars->name, vars->offset, vars->size, typ_ptr, vars->ops);
					}
					vars++;

				}
			}

		}
	}
	//add_struc_member(id,"n",	0X8,	0x30000400,	-1,	8);
	//use parse_decls to gen the typedefs
	//parse_decls(inputtype, flags=0)
	//result += "}";


	return result;


	//FILE* resfile = nullptr;
	//errno_t err = fopen_s(&resfile, "DoomEternalTypes.py", "wb");

	//if (err == 0 && resfile != nullptr) {
	//    fwrite(result.c_str(), 1, result.length(), resfile);
	//    //fputs(result.c_str(), resfile);
	//    fclose(resfile);
	//}
	//else {
	//    // Handle error, e.g., log or display a message
	//    std::cerr << "Error opening file: DoomEternalTypes.py" << std::endl;
	//}



	//FILE* resfile = nullptr;

	//fopen_s(&resfile, "DoomEternalTypes.py", "wb");

	//fwrite(result.c_str(), 1, result.length(), resfile);
	////fputs(result.c_str(), resfile);
	//fclose(resfile);


}