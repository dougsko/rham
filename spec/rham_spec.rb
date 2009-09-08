require File.expand_path(File.dirname(__FILE__) + '/spec_helper')

describe "Rham" do
    before(:all) do
        $model = "dummy"
        @rig = Rham.new
        @rig.rig_open
    end

    after(:all) do
        @rig.rig_close
    end

    it "setsi/gets the mode" do
        @rig.rig_set_mode("AM", "normal")
        @rig.rig_get_mode.should == "AM"
    end

    it "sets/gets the freq" do
        @rig.rig_set_freq(20000)
        @rig.rig_get_freq.should == "20000.000000"
    end

    it "checks stats" do
        stats = @rig.stats
        stats["mode"].should == "AM"
        stats["freq"].should == "20000.000000"
    end

    it "checks powerstat" do
        @rig.rig_get_powerstat.should == "on"
    end

    it "checks vfo" do
        @rig.rig_get_vfo.should == 0
    end

    it "checks info" do
        @rig.rig_get_info.should == "Nothing much (dummy)"
    end

    it "checks strength" do
        @rig.rig_get_strength.should == 0
    end
end
