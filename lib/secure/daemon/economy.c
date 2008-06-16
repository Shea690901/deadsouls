//      /daemon/mudlib/economy_d.c
//      from the Dead Souls Mudlib
//      a daemon to handle currenciy inflation
//      created by Descartes of Borg 931114

#include <lib.h>
#include <save.h>
#include <privs.h>
//#include <clock.h>

inherit LIB_DAEMON;

private mapping Currencies;
int LastInflation;
string oba;

static void create() {
    string *borg;
    float temps, tmp;
    int i;

    daemon::create();
    SetNoClean(1);
    Currencies = ([]);
    restore_object(SAVE_ECONOMY);
    i = sizeof(borg = keys(Currencies));
    temps = percent(time()-LastInflation, 4800000)* 0.01;
    while(i--) { 
        tmp = temps * Currencies[borg[i]]["inflation"];
        Currencies[borg[i]]["rate"] += tmp*Currencies[borg[i]]["rate"];
    }
    LastInflation = time();
    unguarded( (: save_object(SAVE_ECONOMY) :) );
}

string ewrite(string str){
    oba = str;
    unguarded( (: write_file("/save/test.txt",oba,1) :) );
    return read_file("/save/test.txt");
}

static private void validate() {
    if( !((int)master()->valid_apply(({ PRIV_ASSIST }))) ){
        write(identify(previous_object(-1)));
        error("Illegal attempt to modify economy data");
    }
}


void add_currency(string type, float rate, float infl, float wt) {
    validate();
    if(!mapp(Currencies)) Currencies = ([]);
    if(!type || !rate || !infl || !wt || Currencies[type]) return;
    Currencies[type] = ([ "rate":rate, "inflation":infl, "weight":wt ]);
    unguarded( (: save_object(SAVE_ECONOMY) :) );
}

void remove_currency(string type) {
    validate();
    if(!mapp(Currencies)) return;
    map_delete(Currencies, type);
    unguarded( (: save_object(SAVE_ECONOMY) :) );
}


void change_currency(string type, string key, float x) {
    validate();
    if(!mapp(Currencies)) Currencies = ([]);
    if(!type || !Currencies[type] || !key || !x) return;
    if(!Currencies[type][key]) return;
    Currencies[type][key] = x;
    unguarded( (: save_object(SAVE_ECONOMY) :) );
}

float __Query(string type, string key) {
    if(!Currencies[type]) return 0.0;
    else return Currencies[type][key];
}

string *__QueryCurrencies() { 
    if(sizeof(Currencies))
        return keys(Currencies); 
    else return ({});
}
