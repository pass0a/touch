#include "plugin.h"
#include "../src/touch.h"
#include <iostream>

struct pa_plugin gp;
int reportTouch2(pa_context* ctx) {
    if (gp.is_array(ctx, 0)) {
        int type=0, code=0, value=0;
        int n = gp.get_length(ctx, 0);
        for (int i = 0; i < n; i += 3)
        {
            gp.get_prop_index(ctx, 0, i);
            if (gp.is_number(ctx, -1)) {
                type = gp.get_int(ctx, -1);
            }
            gp.get_prop_index(ctx, 0, i + 1);
            if (gp.is_number(ctx, -1)) {
                code = gp.get_int(ctx, -1);
            }
            gp.get_prop_index(ctx, 0, i + 2);
            if (gp.is_number(ctx, -1)) {
                value=gp.get_int(ctx, -1);
            }
            reportMouse(type, code, value);
        }
    }
    return 0;
}
int reportTouch(pa_context* ctx) {
	for(int idx=0;idx<5;idx++){
		if(!gp.is_number(ctx,idx)){
			return 0;
		}
	}
	TOUCHPOSDATA tcd;
	tcd.ope=(OPERAT)gp.get_int(ctx,0);
	tcd.pos_x1=gp.get_int(ctx,1);
	tcd.pos_y1=gp.get_int(ctx,2);
	tcd.pos_x2=gp.get_int(ctx,3);
	tcd.pos_y2=gp.get_int(ctx,4);
	reportEvent(&tcd);
	return 0;
}
int setTouchDevice(pa_context* ctx){
	if(gp.is_string(ctx,0)){
		setDevice(gp.get_string(ctx,0));
	}
	return 0;
}
static const pa_function_list_entry my_module_funcs[] = {
    { "reportTouch2", reportTouch2, PA_VARARGS /*nargs*/ },
	{ "reportTouch", reportTouch, PA_VARARGS /*nargs*/ },
	{ "setTouchDevice", setTouchDevice, PA_VARARGS /*nargs*/ },
	{ NULL, NULL, 0 }
};
extern "C" int passoa_init(pa_plugin p) {
	gp=p;
	gp.put_function_list(p.ctx, -1, my_module_funcs);
	return 0;
}
extern "C" int passoa_exit() {
	//audioExit();
	return 0;
}
