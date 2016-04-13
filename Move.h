//
//  Move.h
//  Animal
//
//  Created by yang_xiong on 16/4/11.
//
//

#ifndef Move_h
#define Move_h

struct PointXY {
	char x;
	char y;
	bool operator==(const PointXY &p) {
		return (x == p.x && y == p.y);
	}
	bool operator!=(const PointXY &p) {
		return (x != p.x || y != p.y);
	}
	PointXY(int _x,int _y):x(_x),y(_y){}
	PointXY(){}
};

struct Move{
    PointXY from;
    PointXY to;
};

#endif /* Move_h */
