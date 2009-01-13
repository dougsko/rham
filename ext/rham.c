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
	rig_model_t my_model = RIG_MODEL_DUMMY;
	//rig_model_t my_model = RIG_MODEL_FT847;	

	my_rig = rig_init(my_model);
	if (!my_rig) 
		fprintf(stderr,"Unknown rig num: %d\n", my_model);

	return Data_Wrap_Struct(self, rig_mark, rig_free, my_rig);
}

static VALUE rb_rig_open(VALUE self){
	RIG *my_rig;
	int ret;

	Data_Get_Struct(self, RIG, my_rig);
	
	if((ret = rig_open(my_rig)) != RIG_OK)
		 printf("rig_open: error = %s\n", rigerror(ret));
	else
		return Qnil;
}

static VALUE rb_rig_close(VALUE self){
	RIG *my_rig;
	int ret;

	Data_Get_Struct(self, RIG, my_rig);

	if((ret = rig_close(my_rig)) != RIG_OK)
		printf("rig_open: error = %s\n", rigerror(ret));
	else
		return Qnil;	
}

static VALUE rb_rig_get_info(VALUE self){
	RIG *my_rig;
	const char *info;

	Data_Get_Struct(self, RIG, my_rig);

	info = rig_get_info(my_rig);
	if(!info)
		return Qnil;
	return rb_str_new2(info);
}

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

static VALUE rb_rig_get_vfo(VALUE self){
	RIG *my_rig;
	vfo_t *vfo;

	Data_Get_Struct(self, RIG, my_rig);
	return INT2NUM(rig_get_vfo(my_rig, &vfo));
}

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


void Init_rham() {
	rb_cRham = rb_define_class("Rham", rb_cObject);
	rb_define_alloc_func(rb_cRham, rig_allocate);
	rb_define_method(rb_cRham, "rig_open", rb_rig_open, 0);
	rb_define_method(rb_cRham, "rig_close", rb_rig_close, 0);
	rb_define_method(rb_cRham, "rig_get_info", rb_rig_get_info, 0);
	rb_define_method(rb_cRham, "rig_get_freq", rb_rig_get_freq, 0);
	rb_define_method(rb_cRham, "rig_get_vfo", rb_rig_get_vfo, 0);
	rb_define_method(rb_cRham, "rig_get_powerstat", rb_rig_get_powerstat, 0);
	//rb_define_method(rb_cSpike, "set_spike", rb_set_spike, 0);
	//rb_define_method(rb_cSpike, "init_fuzz", rb_init_fuzzing, 0);
	//rb_define_method(rb_cSpike, "cstring", rb_cstring, 1);
	//rb_define_method(rb_cSpike, "unistring", rb_unistring, 1);
}
