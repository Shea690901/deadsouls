#include <lib.h>
#include <daemons.h>

inherit LIB_DAEMON;
string tmp;

mixed cmd(string args) {
    int x,c;
    string filenames;
    string *ret_arr;

    if( !((int)master()->valid_apply(({ "ASSIST" }))) &&
      base_name(previous_object()) != "/secure/cmds/creators/findfun" && 
      base_name(previous_object()) != "/secure/cmds/creators/showfuns" )
	error("Illegal attempt to access file command: "+
	  get_stack()+" "+identify(previous_object(-1)));

    if(args){
	if(grepp(args,"-x ")){
	    args = replace_string(args,"-x ","");
	    x = 1;
	    tmp = args;
	}
	if(grepp(args,"-c ")){
	    args = replace_string(args,"-c ","");
	    c = 1;
	    tmp = args;
	}
    }

    if(!c){
	shout("%^YELLOW%^File daemon is scanning all files. Please wait...");
	flush_messages();
	FILE_D->eventHarvestDirs();
	FILE_D->eventHarvestFiles();
	shout("%^GREEN%^File scan complete.");
    }
    write("Number of directories: "+sizeof(FILE_D->GetDirs()));
    filenames = FILE_D->GetFiles();
    write("Number of files: "+sizeof(filenames));
    if(!args || args == "")    return 1;
    if(!strsrch(args,"-x ")){
	args = replace_string(args,"-x ","");
	x = 1;
	tmp = args;
    }
    ret_arr = regexp(filenames, args);
    if(x) ret_arr = filter(ret_arr, (: !strsrch($1, tmp) :) );
    if(interactive(previous_object())){
	write(implode(ret_arr,"\n"));
	return 1;
    }
    else return ret_arr;
}

void help() {
    message("help", "Syntax: <files [-x] [-c] [SUBSTRING]>\n\n"
      "With no arguments, this command reloads the file "
      "daemon's data. If given a substring, it will also search "
      "filenames and return those with the substring in their path. "
      "With a substring and the -x flag, it will only return "
      "filenames whose paths *begin* with the substring. " 
      "The -c flag skips the reloading of file daemon data, which "
      "saves time and avoids mud-wide lag, but may return outdated "
      "information."
      "\n\n"
      "", this_player());
}
