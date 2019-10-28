const t = require('./touch.passoa');
declare function sleep(time: number): void
class Touch {
	tick: number = 0;
	setDevice(path: string) {
		return t.setTouchDevice(path);
	}
	mark(x: number, y: number) {
		var mk = [ 3, 53, x, 3, 54, y, 3, 0, x, 3, 1, y, 0, 0, 0 ];
		t.reportTouch2(mk);
	}
	down(x: number, y: number) {
		var press = [ 3, 57, this.tick, 3, 53, x, 3, 54, y, 1, 330, 1, 3, 0, x, 3, 1, y, 0, 0, 0 ];
		t.reportTouch2(press);
	}
	up(x: number, y: number) {
		var release = [ 3, 57, -1, 1, 330, 0, 0, 0, 0 ];
		t.reportTouch2(release);
	}
	click(x: number, y: number) {
		this.down(x, y);
		sleep(100);
		this.up(x, y);
		//t.reportTouch(0,x,y,x,y);
		//this.hold(x,y,100);
	}
	move(x1: number, y1: number, x2: number, y2: number) {
		var eplased = 0;

		this.down(x1, y1);
		sleep(100);
		this.mark(x2, y2);
		sleep(10);
		this.up(x2, y2);
		// t.reportTouch(2,x1,y1,x2,y2);
	}
	hold(x: number, y: number, time: number) {
		this.down(x, y);
		sleep(time);
		this.up(x, y);
		// var eplased=0;

		// t.reportTouch(0,x,y,x,y);
		// while(eplased<time){
		// sleep(50);
		// eplased+=50;
		// //t.reportTouch(0,x,y,x,y);
		// }
		// t.reportTouch(1,x,y,x,y);
	}
}

export let tmp = new Touch();
