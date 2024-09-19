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

}



std::vector<addrName> IdaScriptsGen::getAddrNamesForCvar(idCVar* cvarPtr) {
	std::vector<addrName> resultVec;

	if (!cvarPtr) {
		logErr("getAddrNamesForCvar: cvarPtr is nullptr !");
		return resultVec;
	}

	// Helper lambda to simplify adding entries to resultVec
	auto addAddrName = [&](const std::string& suffix, uint64_t address) {
		addrName entry;
		if (address) {
			//logInfo("addAddrName: dbg: name: %s address: %p ", suffix.c_str(), (void*)address);
			entry.name = "cvar_" + std::string(cvarPtr->name) + suffix;
			entry.rva_address = address - MemHelper::getModuleBaseAddr();
			resultVec.push_back(entry);
		}		
	};

	// Add various address names with corresponding suffixes
	addAddrName("", (uint64_t)cvarPtr);
	addAddrName("_valStrings", (uint64_t)&cvarPtr->valueStrings);
	addAddrName("_int", (uint64_t)&cvarPtr->valueInteger);
	addAddrName("_float", (uint64_t)&cvarPtr->valueFloat);
	addAddrName("_valMax", (uint64_t)&cvarPtr->valueMax);
	addAddrName("_valMin", (uint64_t)&cvarPtr->valueMin);
	addAddrName("_valSecs", (uint64_t)&cvarPtr->valueSeconds);
	addAddrName("_valMillis", (uint64_t)&cvarPtr->valueMilliseconds);
	addAddrName("_valMicros", (uint64_t)&cvarPtr->valueMicroseconds);
	addAddrName("_flags", (uint64_t)&cvarPtr->flags);
	//? don't need this there is litterally 2 cvars which have onchange and they're irrelevant to us.
	//addAddrName("_onChange", (uint64_t)cvarPtr->onChange);

	return resultVec;
}




std::vector<addrName> IdaScriptsGen::getCvarsAddrNamesVec() {

	std::vector<addrName> allAddrNamesVec;

	size_t cvarsCounter = 0;

	idList* cvarIdList = idCvarManager::getCVarlist();
	if (!cvarIdList) {
		logErr("getCvarsAddrNamesVec: cvarIdList is null");
		return allAddrNamesVec;
	}

	logInfo("getCvarsAddrNamesVec: dbg: cvarIdList->num: %d", cvarIdList->num);

	for (size_t i = 0; i < cvarIdList->num; i++) {
		idCVar* cvarPtr = (idCVar*)cvarIdList->list[i];
		if (!cvarPtr) continue;

		// Get the address names for the current cvar
		std::vector<addrName> cvarAddrNamesVec = IdaScriptsGen::getAddrNamesForCvar(cvarPtr);

		// Add all the elements of cvarAddrNamesVec to allAddrNamesVec
		allAddrNamesVec.insert(allAddrNamesVec.end(), cvarAddrNamesVec.begin(), cvarAddrNamesVec.end());
	}

	return allAddrNamesVec;
}



addrName IdaScriptsGen::getAddrNameForCmd(commandDef_s* cmdDef) {

	addrName entry;
	entry.name = "cmd_" + std::string(cmdDef->name);
	entry.rva_address = ((uint64_t)cmdDef->function) - MemHelper::getModuleBaseAddr();
	return entry;
}


std::vector<addrName> IdaScriptsGen::getCmdsAddrNamesVec() {

	size_t cmdCounter = 0;
	std::vector<addrName> allAddrNamesVec;;


	idList* cmdIdList = idCmdManager::getCmdlist();
	if (!cmdIdList) {
		logErr("getCmdsAddrNamesVec: cmdIdList is null");
		return allAddrNamesVec;
	}

	//logInfo("getCmdsAddrNamesVec: dbg: cmdIdList->num: %d", cmdIdList->num);


	for (size_t i = 0; i < cmdIdList->num; i++)
	{
		commandDef_s* cmdDef = (commandDef_s *) cmdIdList->list[i];
		if (!cmdDef) continue;

		allAddrNamesVec.push_back(getAddrNameForCmd(cmdDef));

		//logInfo("entry: %s f: %p", entry.name.c_str(), (void*)entry.rva_address);
	}

	return allAddrNamesVec;

}



addrName IdaScriptsGen::getAddrNameForEvent(idEventDef* eventDefPtr) {

	addrName data = addrName(std::string(), 0);

	if (!eventDefPtr || !eventDefPtr->name) {
		logErr("getAddrName: !eventDefPtr || !eventDefPtr->name");
		return data;
	}

	data.name = "eventDef_";
	data.name += eventDefPtr->name;

	data.rva_address = (uint64_t)eventDefPtr - MemHelper::getModuleBaseAddr();

	return data;
}




std::vector<addrName> IdaScriptsGen::getEventsAddrNamesVec() {

	std::vector<idEventDef*> eventDefsPtrs = idEventManager::getEventsVec();
	std::vector<addrName> resultVec;

	for (size_t i = 0; i < eventDefsPtrs.size(); i++)
	{
		resultVec.push_back(getAddrNameForEvent(eventDefsPtrs[i]));
	}

	return resultVec;

}




std::vector<addrName> IdaScriptsGen::getAllAddrNamesVec()
{
	std::vector<addrName> cvarDataVec = getCvarsAddrNamesVec();
	std::vector<addrName> cmdDataVec = getCmdsAddrNamesVec();
	std::vector<addrName> eventsDataVec = getEventsAddrNamesVec();

	// Create a combined vector to store all elements
	std::vector<addrName> combinedDataVec;

	// Reserve space to avoid multiple reallocations (optional, but improves performance)
	combinedDataVec.reserve(cvarDataVec.size() + cmdDataVec.size() + eventsDataVec.size());

	// Insert elements from the first vector
	combinedDataVec.insert(combinedDataVec.end(), cvarDataVec.begin(), cvarDataVec.end());

	// Insert elements from the second vector
	combinedDataVec.insert(combinedDataVec.end(), cmdDataVec.begin(), cmdDataVec.end());

	// Insert elements from the third vector
	combinedDataVec.insert(combinedDataVec.end(), eventsDataVec.begin(), eventsDataVec.end());

	return combinedDataVec;

}



std::string IdaScriptsGen::get_address_name_list_Line_AsStr(addrName data) {

	std::string resultStr;

	if (data.name.empty() || data.rva_address == 0) {
		return std::string();
	}

	std::string filteredNameStr = K_Utils::removeSpaces(data.name);

	return "(" + K_Utils::intToHexString(data.rva_address) + ", \"" + filteredNameStr + "\"),\n";
	
}


void IdaScriptsGen::generateRenameVarsPythongScript()
{
	std::vector<addrName> combinedDataVec = getAllAddrNamesVec();

	std::string resultAsStr = "import idaapi\n\n";
	resultAsStr += "address_name_list = [\n";
	//std::string fourSpaces = "    ";

	logInfo("generateRenameVarsPythongScript: debug: loggin addrName vec: ");

	for (addrName data : combinedDataVec)
	{
		resultAsStr += get_address_name_list_Line_AsStr(data);
		//logInfo("name: %s addr: %p", data.name.c_str(), (void*)data.rva_address);
	}
	resultAsStr += "]\n\n";
	resultAsStr += "def rename_addresses(address_name_list):\n";
	resultAsStr += "    for address, name in address_name_list:\n";
	resultAsStr += "        result = idaapi.set_name(address, name, idaapi.SN_CHECK)\n";
	resultAsStr += "        if result:\n";
	resultAsStr += "            print(f\"Renamed address{ hex(address) } to{ name }\")\n";
	resultAsStr += "        else:\n";
	resultAsStr += "            print(f\"Failed to rename address{ hex(address) }\")\n\n";
	resultAsStr += "# Call the function to rename addresses\n";
	resultAsStr += "rename_addresses(address_name_list)\n";

	std::string fileName = "IdaScript_Wolf2_Rename_Vars.py";

	K_Utils::saveStrToFile(fileName, resultAsStr);

}