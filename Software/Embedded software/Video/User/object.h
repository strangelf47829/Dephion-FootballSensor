/*
 * object.h
 *
 *  Created on: Oct 11, 2022
 *      Author: Rafael de Bie
 */

#ifndef OBJECT_H_
#define OBJECT_H_

class object {
public:
	object();
	virtual ~object();
	object(const object &other);
	object(object &&other);
	object& operator=(const object &other);
	object& operator=(object &&other);
};

#endif /* OBJECT_H_ */
