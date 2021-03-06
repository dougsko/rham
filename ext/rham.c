#include "ruby.h"
#include <stdio.h>
#include <hamlib/rig.h>

static VALUE rb_cRham;

static void rig_mark(RIG *my_rig){
}

static void rig_free(RIG *my_rig){
	rig_cleanup(my_rig);	
}

static VALUE rig_allocate(VALUE self){
	RIG *my_rig;
	rig_model_t my_model;
    char *model;

    if(model = STR2CSTR(rb_gv_get("$model"))){
        if(model == "ft847"){
            my_model = RIG_MODEL_FT847;
        }
        else{
            my_model = RIG_MODEL_DUMMY;
        }
    }
    else{
        fprintf(stderr,"You must define the global variable, $model, somewhere in your script");
    }

	rig_set_debug(RIG_DEBUG_NONE);
	my_rig = rig_init(my_model);
	if (!my_rig) 
		fprintf(stderr,"Unknown rig num: %d\n", my_model);

	return Data_Wrap_Struct(self, rig_mark, rig_free, my_rig);
}

/* Open a connection to a rig.
 * 
 *   rig.rig_open
 */
static VALUE rb_rig_open(VALUE self){
	RIG *my_rig;
	int ret;

	Data_Get_Struct(self, RIG, my_rig);

	if((ret = rig_open(my_rig)) != RIG_OK)
		 printf("rig_open: error = %s\n", rigerror(ret));
	else
		return Qnil;
}

/* Close the connection to a rig. */
static VALUE rb_rig_close(VALUE self){
	RIG *my_rig;
	int ret;

	Data_Get_Struct(self, RIG, my_rig);

	if((ret = rig_close(my_rig)) != RIG_OK)
		printf("rig_close: error = %s\n", rigerror(ret));
	else
		return Qnil;	
}

/* Returns information about the rig. */
static VALUE rb_rig_get_info(VALUE self){
	RIG *my_rig;
	const char *info;

	Data_Get_Struct(self, RIG, my_rig);

	info = rig_get_info(my_rig);
	if(!info)
		return Qnil;
	return rb_str_new2(info);
}

/* Returns the frequency the rig is tuned to.
 *
 *   rig.rig_get_freq    #=> "20000.000000"
 */
static VALUE rb_rig_get_freq(VALUE self){
	RIG *my_rig;
	freq_t freq;
	int ret;
	char result[100];

	Data_Get_Struct(self, RIG, my_rig);
	ret = rig_get_freq(my_rig, RIG_VFO_CURR, &freq);

	if(ret != RIG_OK)
		printf("rig_open: error = %s\n", rigerror(ret));
	else{
		sprintf(result, "%f", freq);	
		return rb_str_new2(result);
	}
	return Qnil;
}

/* Returns the VFO the rig is set to.
 *
 *   rig.rig_get_vfo    #=> 0
 */
static VALUE rb_rig_get_vfo(VALUE self){
	RIG *my_rig;
	vfo_t *vfo;

	Data_Get_Struct(self, RIG, my_rig);
	return INT2NUM(rig_get_vfo(my_rig, &vfo));
}

/* Lets you know whether the rig is turned on or off.
 *
 *   rig.rig_get_powerstat    #=> "on"
 */
static VALUE rb_rig_get_powerstat(VALUE self){
	RIG *my_rig;
	powerstat_t *status;
	int ret;

	Data_Get_Struct(self, RIG, my_rig);
	ret = rig_get_powerstat(my_rig, &status);	

	if(ret != RIG_OK){
		printf("rig_get_powerstat: error = %s\n", rigerror(ret));
		return Qnil;
	}
	if(status == RIG_POWER_OFF)
		return rb_str_new2("off");
	else if(status == RIG_POWER_ON)
		return rb_str_new2("on");
	else
		return Qnil;
}

/* Sets the frequency of the rig.
 *
 *   rig.rig_set_freq(20000)    #=> nil
 */
static VALUE rb_rig_set_freq(VALUE self, VALUE rfreq){
	int ret;
	freq_t freq;
	RIG *my_rig;
	
	freq = NUM2LONG(rfreq);
	Data_Get_Struct(self, RIG, my_rig);
	ret = rig_set_freq(my_rig, RIG_VFO_CURR, freq);
	if(ret != RIG_OK)
		printf("rig_set_freq: error = %s\n", rigerror(ret));
	
	return Qnil;
}	

/* Returns the strength of the signal.
 *
 *   rig.rig_get_strength    #=> 0
 */
static VALUE rb_rig_get_strength(VALUE self){
	int ret;
	int strength;
	RIG *my_rig;

	Data_Get_Struct(self, RIG, my_rig);
	ret = rig_get_strength(my_rig, RIG_VFO_CURR, &strength);
	if(ret != RIG_OK)
		printf("rig_get_strength: error = %s\n", rigerror(ret));
	else
		return INT2NUM(strength);

	return Qnil;
}

/* Returns the mode the rig is set to.
 *
 *   rig.rig_get_mode    #=> "AM"
 */
static VALUE rb_rig_get_mode(VALUE self){
	int ret;
	rmode_t mode;
	pbwidth_t width;
	RIG *my_rig;

	Data_Get_Struct(self, RIG, my_rig);
	ret = rig_get_mode(my_rig, RIG_VFO_CURR, &mode, &width);
	
	if(ret != RIG_OK)
		printf("rig_get_mode: error = %s\n", rigerror(ret));
	else
		return rb_str_new2(rig_strrmode(mode));

	return Qnil;
}

/* Set the mode of the rig.  The second argument can be either,
 * "normal", "wide", or "narrow".
 *
 *   rig.rig_set_mode("FM", "normal")    #=> nil
 */    
static VALUE rb_rig_set_mode(VALUE self, VALUE rmode, VALUE rwidth){
	int ret;
	rmode_t mode;
	pbwidth_t width;
	RIG *my_rig;
	char *s_width;

	Data_Get_Struct(self, RIG, my_rig);

	mode = rig_parse_mode(STR2CSTR(rmode));

	s_width = STR2CSTR(rwidth);
	if(strcmp(s_width, "normal") == 0)
		width = rig_passband_normal(my_rig, mode);
	else if(strcmp(s_width, "narrow") == 0)
		width = rig_passband_narrow(my_rig, mode);
	else if(strcmp(s_width, "wide") == 0)
		width = rig_passband_wide(my_rig, mode);
	else
		printf("rig_set_mode: error = Invalid width");		

	ret = rig_set_mode(my_rig, RIG_VFO_CURR, mode, width);
        if(ret != RIG_OK)
                printf("rig_set_mode: error = %s\n", rigerror(ret));

        return Qnil;
}	

/* This is where all of the methods are registered */
void Init_rham() {
	rb_cRham = rb_define_class("Rham", rb_cObject);
	rb_define_alloc_func(rb_cRham, rig_allocate);
	//rb_define_method(rb_cRham, "new", rb_new, 1);
	rb_define_method(rb_cRham, "rig_open", rb_rig_open, 0);
	rb_define_method(rb_cRham, "rig_close", rb_rig_close, 0);
	rb_define_method(rb_cRham, "rig_get_info", rb_rig_get_info, 0);
	rb_define_method(rb_cRham, "rig_get_freq", rb_rig_get_freq, 0);
	rb_define_method(rb_cRham, "rig_get_vfo", rb_rig_get_vfo, 0);
	rb_define_method(rb_cRham, "rig_get_powerstat", rb_rig_get_powerstat, 0);
	rb_define_method(rb_cRham, "rig_set_freq", rb_rig_set_freq, 1);
	rb_define_method(rb_cRham, "rig_get_strength", rb_rig_get_strength, 0);
	rb_define_method(rb_cRham, "rig_get_mode", rb_rig_get_mode, 0);
	rb_define_method(rb_cRham, "rig_set_mode", rb_rig_set_mode, 2);
}
