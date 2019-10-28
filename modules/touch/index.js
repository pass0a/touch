const t=require("./touch.passoa");

function Touch(){
	this.tick=0;
}
Touch.prototype.setDevice=function(path){
	return t.setTouchDevice(path);
}
Touch.prototype.mark=function(x,y){
	var mk=[
		3,53,x,
		3,54,y,
		3,0,x,
		3,1,y,
		0,0,0,
	];
	t.reportTouch2(mk);
}
Touch.prototype.down=function(x,y){
	var press=[
		3,57,this.tick,
		3,53,x,
		3,54,y,
		1,330,1,
		3,0,x,
		3,1,y,
		0,0,0,
	];
	t.reportTouch2(press);
	
}
Touch.prototype.up=function(x,y){
	var release=[
		3,57,-1,
		1,330,0,
		0,0,0,
	];
	t.reportTouch2(release);
	
}
Touch.prototype.click=function(x,y){
	this.down(x,y);
	sleep(100);
	this.up(x,y);
	//t.reportTouch(0,x,y,x,y);
	//this.hold(x,y,100);
}
Touch.prototype.move=function(x1,y1,x2,y2){
	var eplased=0;

	this.down(x1,y1);
	sleep(100);
	this.mark(x2,y2);
	sleep(10);
	this.up(x2,y2);
	// t.reportTouch(2,x1,y1,x2,y2);
}
Touch.prototype.hold=function(x,y,time){
	this.down(x,y);
	sleep(time);
	this.up(x,y);
	// var eplased=0;

	// t.reportTouch(0,x,y,x,y);
	// while(eplased<time){
		// sleep(50);
		// eplased+=50;
		// //t.reportTouch(0,x,y,x,y);
	// }
	// t.reportTouch(1,x,y,x,y);
}
module.exports=new Touch();
