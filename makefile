Test7:	Test7.cpp Time.o Timing.o Event.o Schedulable.o Professor.o Group.o Classroom.o Exception.o TimeException.o TimingException.o XmlFileSerializerException.o
		g++ Test7.cpp  Time.o Timing.o Event.o Schedulable.o Professor.o Group.o Classroom.o Exception.o TimeException.o TimingException.o XmlFileSerializerException.o -o Test7

Event.o:	Event.cpp Event.h
			g++ Event.cpp -c
	
Time.o:		Time.cpp Time.h TimeException.h
			g++ Time.cpp -c

Timing.o:	Timing.cpp Timing.h
			g++ Timing.cpp -c

Schedulable.o:	Schedulable.cpp Schedulable.h
				g++ Schedulable.cpp -c

Professor.o:	Professor.cpp Professor.h Schedulable.h
				g++ Professor.cpp -c

Group.o:		Group.cpp Group.h Schedulable.h
				g++ Group.cpp -c

Classroom.o:	Classroom.cpp Classroom.h Schedulable.h
				g++ Classroom.cpp -c

Exception.o:	Exception.cpp Exception.h
				g++ Exception.cpp -c

TimeException.o:	TimeException.cpp TimeException.h Exception.h
					g++ TimeException.cpp -c

TimingException.o:	TimingException.cpp TimingException.h Exception.h
					g++ TimingException.cpp -c

XmlFileSerializerException.o:	XmlFileSerializerException.cpp XmlFileSerializerException.h Exception.h
								g++ XmlFileSerializerException.cpp -c