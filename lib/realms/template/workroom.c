#include <lib.h>
#include <rooms.h>
#include "./customdefs.h"

inherit LIB_ROOM;
int ReadSign();
int ReadSheet();
int privacy = 0;
string privs = "";
string LongString(){
    string ret = "You are standing in the workroom of the mighty " + privs +
    "!  \nYou may return to the Creators' Hall by going down.\n"+
    "A sample room is east."+
    "\n%^GREEN%^There is a sign here you can read.%^RESET%^"+
    "\n%^GREEN%^There is a sheet here you can read.%^RESET%^";
    if(privacy) ret += "\n%^YELLOW%^There is a privacy force field "+
	"active around this room.%^RESET%^";
    return ret;
}

static void create() {
    room::create();
    privs = query_privs();
    if( privs ) privs = capitalize(privs);
    else privs = "a creator";

    SetClimate("indoors");
    SetAmbientLight(40);
    SetShort(possessive_noun(privs) + " workroom");
    SetLong( (: LongString :) );
    SetItems( ([ "workroom" : "It looks very nice.",
	({"sign","hint","hints"}) : "A sign with hints for creators.",
	({"sheet","reminder","reminders"}) : "A sheet with quick reminders for creators.",
      ]) );
    SetRead( ([
	({"sign","hint","hints"}) : (: ReadSign :),
	({"sheet","reminder","reminders"}) : (: ReadSheet :)
      ]) );
    SetInventory( ([
	MY_OBJ "/chest" : 1,
	"/domains/default/obj/bbucket" :1,
      ]) );
    SetExits( ([ "down" : "/domains/default/room/wiz_hall.c",
	"east" : MY_ROOM "/sample_room"
      ]) );
    SetNoModify(1);
}

int ReadSign(){
    this_player()->eventPage("/news/hints.txt");
    return 1;
}

int ReadSheet(){
    this_player()->eventPage("/news/reminders.txt");
    return 1;
}

void init(){
    ::init();
    add_action("mod_privacy","privacy");
    add_action("mod_privacy","priv");
}
int CanReceive(object ob) {
    if(privacy){
	if(!interactive(ob)) {
	    message("info","\n\nPRIVACY WARNING: "+ob->GetName()+" has entered the room.\n\n",this_object() );
	}
	else if(!archp(ob) &&
	  ob->GetKeyName() != lower_case(privs)){
	    message("info","You bounce off the privacy field.", ob);
	    message("info",ob->GetName()+" bounced off the privacy field.",this_object());
	    if(!environment(ob)) ob->eventMoveLiving(ROOM_START);
	    return 0;
	}
    }
    return room::CanReceive(ob);
}

static int set_privacy(int i){
    privacy=i;
    return 1;
}

static int mod_privacy(string str){
    if(!archp(this_player()) &&
      this_player()->GetKeyName() != lower_case(privs)) {
	write("You lack the adequate privileges to do that.");
	say(this_player()->GetName()+" is trying to muck around with the privacy field system.");
	return 1;
    }
    if(!str || str == ""){
	if(privacy) str = "off";
	else str = "on";
    }
    if(str=="on" || str == "1"){
	set_privacy(1);
	write("You enable the privacy field.\n");
	say(this_player()->GetName()+" enables a privacy force field around the
room.");
        return 1;
    }
    if(str=="off" || str == "0"){
        set_privacy(0);
        write("You disable the privacy field.\n");
        say(this_player()->GetName()+" disables a privacy force field around the room.");
        return 1;
    }
}


