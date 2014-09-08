#include "core.h"
#include "serverManager.h"
#include "serverCore.h"
#include "question.h"

// Global variables
Monitor monitor;
ServerManager manager;
Question question;
// Protoype function
// Main method
int main()
{
	// Create a monitor and register function for it
	monitor = newMonitor();
	// Create a server manager ans register function for it
	manager = newServerManager();
	// Register function for manager
	question = createQuestion();
	// Now run server
	// Create server
	Server server;
	init(&server,&monitor,&manager,question);
	// Register processing function for server
	
	//Now run
	server.run(&server);
	return 0;
}
