#pragma once

class Subject;  //Parce qu'on sera en forward declaration

class IObserver
{
public:
	virtual void Notify(Subject* _subject) = 0;
};
