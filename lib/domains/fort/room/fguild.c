/* 
File created with Roommaker 
written by Haderach@Frontiers 
Room made by Cratylus
Date: Wed Oct 19 12:39:28 2005
WARNING! WARNING! If you edit this room by hand the room maker may be unable to read
it properly. Hand-edit at your own risk.

*/

#include <lib.h>
#include "../customdefs.h";
inherit LIB_ROOM;

static void create() {
    room::create();
    SetTown("fort");
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("Fighters' guild");
    SetLong("The guild of the fighters.");
    SetProperties (([
	"no attack":0, 
	"no bump":0, 
	"no steal":0, 
	"no magic":0, 
	"no paralyze":0, 
	"no teleport":0]));
    SetItems(([]));
    SetInventory(([]));
    SetObviousExits("s");
    AddExit("out", MY_ROOM + "/" +"gstreet5");
    AddExit("south", MY_ROOM + "/" +"gstreet5");
    //funs
    //snuf
}
void init() {
    ::init();
    SetSmell(([]));
    SetListen(([]));
}
//extras
