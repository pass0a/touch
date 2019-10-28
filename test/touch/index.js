const t=require("touch");
t.setDevice("/dev/input/event1");
t.click(251,357);
sleep(2000);
t.move(109,341,105,177);
sleep(1000);
t.hold(89,332,1000);
