#include "../../include/driver_manager.h"

int main(void)
{
    printf("\a");

    /* Enter 'Username', 'Password' & 'Hostname' as per your entered credentials. */

    setConnection("Gourav", "lightofgod", "Gouraarav", 8080, "Gourav", "lightofgod", FALSE);

    interpret("SHOW ALL DB");
    interpret("MAKE DB mydb");
    interpret("SHOW ALL DB");

    endConnection();

    return 0;
}