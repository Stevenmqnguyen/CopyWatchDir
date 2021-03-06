/*
 * Filename	parseConfigFile.cc
 * Date 	May 9, 2021
 * Author	Steven Nguyen
 * Email	steven.nguyen@utdallas.edu
 * Course	CS 3377.0W5 Spring 2021
 * Version 	1.0
 * Copyright	2021, All Rights Reserved
 *
 * Description
 * 	Daemon process that will watch a folder and respond to specific file operations that occur in that folder.
 *	The daemon will read its configuration parameters from a CONFIG file and then operate according to that configuration.
 *  When it detects a write, the daemon will immediately create a copy of the just written file and store that copy in a
 *  .versions subfolder. Each copy stored in the .versions subfolder will have a date stamp appended to the filename.
 *
 */
#include <map>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "rude/config.h"
#include "parseConfigFile.h"
#include "enum.h"
#include "globals.h"

using namespace std;
using namespace rude;

void parseConfig(){
    Config config;
	if(config.load(g_optionMap[config_filename].c_str())){
		if(!config.setSection("Parameters", false)){
			cerr << "Config file is missing section: Parameters" << endl;
			exit(1);
		}
		if(config.exists("Verbose") 
		&& config.exists("LogFile") 
		&& config.exists("Password") 
		&& config.exists("NumVersions")
		&& config.exists("WatchDir")){
			g_optionMap[verbose] = config.getStringValue("Verbose");
			g_optionMap[logfile_filename] = config.getStringValue("LogFile");
			g_optionMap[password] = config.getStringValue("Password");
			g_optionMap[numVersions] = config.getStringValue("NumVersions");
			string dir = config.getStringValue("WatchDir");
			size_t pos = dir.find_last_of("/");
			if(pos == dir.length()-1){
    			dir.erase(dir.length()-1);
			}
			g_optionMap[watchdir] = dir;
			dir = g_optionMap[watchdir]+"/.versions";
			g_optionMap[versionsDir] = dir;
		}
		else{
			cerr << "Config file is missing one or more definitions." << endl;
            exit(1);
		}
	}
	else{
		// loading the config file failed
		cerr << "Error loading config file: " << config.getError() << endl;
        exit(1);
	}
}
void reparseConfig(){
    Config config;
	if(config.load(g_optionMap[config_filename].c_str())){
		if(!config.setSection("Parameters", false)){
			cerr << "Config file is missing section: Parameters" << endl;
			exit(1);
		}
		if(config.exists("Verbose") 
		&& config.exists("LogFile") 
		&& config.exists("Password") 
		&& config.exists("NumVersions")
		&& config.exists("WatchDir")){
			g_optionMap[verbose] = config.getStringValue("Verbose");
			g_optionMap[logfile_filename] = config.getStringValue("LogFile");
			//optionMap[password] = g_optionMap[password];
			g_optionMap[numVersions] = config.getStringValue("NumVersions");
			//optionMap[watchdir] = g_optionMap[watchdir];
		}
		else{
			cerr << "Config file is missing one or more definitions." << endl;
            exit(1);
		}
	}
	else{
		// loading the config file failed
		cerr << "Error loading config file: " << config.getError() << endl;
        exit(1);
	}
}