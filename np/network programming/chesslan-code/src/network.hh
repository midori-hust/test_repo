/* $Revision: 2 $

*/


#ifndef _NETWORK_HH
#  define _NETWORK_HH

class network
{  
	public:
     	network();
		virtual ~network();
		bool send(); /* Puts move/event in queue to
						be sent over existing connection
						from constructor 
					*/
	protected:
		char m_socket;
		bool receive(); // for daemon

};
#endif