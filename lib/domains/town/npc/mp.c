#include <lib.h>
inherit LIB_NPC;

static void create(){
    npc::create();
    SetKeyName("gate guard");
    SetId(({"human","guard","mp","soldier","policeman","military policeman"}));
    SetAdjectives(({"military"}));
    SetShort("a military gate guard");
    SetLong("This is a United States Army military policeman. He has "+
      "spent many months in arduous training, and by the looks of him, has seen "+
      "plenty of action in his lifetime.  He is extremely large, looks very "+
      "tough, and whatever he is guarding is probably very safe.");
    SetInventory(([
        "/domains/town/armor/bdu" : "wear bdu",
        "/domains/town/armor/helmet2" : "wear helmet",
        "/domains/town/weap/m16rifle_mp" : "wield rifle",
      ]));
    SetLevel(20);
    SetRace("human");
    SetClass("fighter");
    SetGender("male");
}
void init(){
    ::init();
}
