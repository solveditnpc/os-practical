#include<iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter size of table (buffer size): ";
    cin >> n;

    int buffer[n];  // Our table (fixed size)
    int count = 0;  // How many items currently on table

    int choice, item;

    while (true) {
        cout << "\n1. Produce\n2. Consume\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // PRODUCER
                if (count == n) {
                    cout << "Table full! Chef waits...\n";
                } else {
                    cout << "Enter item to produce (food ID): ";
                    cin >> item;
                    buffer[count] = item; // Add item at next free spot
                    count++; // One more item on table
                    cout << "Chef produced item: " << item << endl;
                }
                break;

            case 2: // CONSUMER
                if (count == 0) {
                    cout << "Table empty! Customer waits...\n";
                } else {
                    item = buffer[0]; // Take the first item (like front of queue)
                    // Shift all remaining items forward
                    for (int i = 0; i < count-1; i++) {
                        buffer[i] = buffer[i+1];
                    }
                    count--; // One less item
                    cout << "Customer consumed item: " << item << endl;
                }
                break;

            case 3: // EXIT
                cout << "Exiting...Bye!\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }
}