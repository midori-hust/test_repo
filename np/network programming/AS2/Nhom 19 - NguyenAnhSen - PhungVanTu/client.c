#include "clientCore.h"
int main()
{
	Monitor monitor = newMonitor();
	Client client = newClient(&monitor,TRUE);
	client.run(&client);
	return 0;
}
