#include <iostream>
#include <string>
#include <cstdlib> //randomly number generate krny k liye
#include <iomanip> //formatting k liye
using namespace std;
// songnode k liye double linked list bnany k liye class bnai ha
class SongNode   
{
public:
    //title, next, prev
    string title;
    SongNode* next;
    SongNode* prev;
    SongNode(string songTitle) {
        title = songTitle;
        next = NULL;
        prev = NULL;
    }
};

void addSongToStart(SongNode*& head, string songTitle) {
    //new node to add a song to the list
    SongNode* newSong = new SongNode(songTitle);
    //head usko newsong k next py daal dyn
    newSong->next = head;
    //agr pehly sy ha koi head to usk prev m newsong daalo
    if (head != NULL) {
        head->prev = newSong;
    }
    //newsong ko head bna do
    head = newSong;
    cout << "\n\t\t\t   Song '" << songTitle << "' added successfully to the start! \n";
}

void addSongToEnd(SongNode*& head, string songTitle) {
    //agr hmari playlist empty ha to addsongtostart wala function call kr doon gi
    if (head == NULL) {
        addSongToStart(head, songTitle);
        return;
    }
    //aik neya node bna lo
    SongNode* newSong = new SongNode(songTitle);
    //list ko traverse krny k liye
    SongNode* temp = head;
    while (temp->next != NULL) {
        //end node tk ja rhy hain
        temp = temp->next;
    }
    //last node k end m add kr do
    temp->next = newSong;
    //aur jo last node tha usko prev bna do new waly k
    newSong->prev = temp;
    cout << "\n\t\t\t  Song '" << songTitle << "' added successfully to the end! \n";
}

void addSongAfter(SongNode*& head, string afterTitle, string newTitle) {
    //edge case
    if (head == NULL) {
        cout << "\n\t\t\t   Playlist is empty! Cannot add song after another.\n";
        return;
    }
    //traverse krny k liye
    SongNode* temp = head;
    while (temp != NULL && temp->title != afterTitle) {
        temp = temp->next;
    }
    //mila nhi ha song hmy to bs print kra do
    if (temp == NULL) {
        cout << "\n\t\t\t   Song '" << afterTitle << "' not found in the playlist!\n";
        return;
    }
    //new node new song add krny ha wo wala
    SongNode* newSong = new SongNode(newTitle);
    //jis song k aagay new song add krna ha usk aagay wala jo tha ab usko new song ka next bnana ha
    newSong->next = temp->next;
    //new song k previous m temp daal do which is the song jisk aagay hm new song daaala ha
    newSong->prev = temp;
    //jis k aagay hm ny add krna tha agr wo last song nhi ha to usk next k prev m new song add kryn gy
    if (temp->next != NULL) {
        temp->next->prev = newSong;
    }
    //adding new song to temp k next
    temp->next = newSong;

    cout << "\n\t\t\t   Song '" << newTitle << "' added successfully after '" << afterTitle << "'! \n";
}

void deleteSong(SongNode*& head, int pos) {
    if (head == NULL) {
        cout << "\n\t\t\t   Playlist is empty! Cannot delete.\n";
        return;
    }
    if (pos == 1) {
        SongNode* toDelete = head;
        head = head->next;
        //head jo ha wo null nhi ha to uska prev ko null kr dyn
        if (head != NULL) {
            head->prev = NULL;
        }
        cout << "\n\t\t\t  Song '" << toDelete->title << "' deleted successfully! \n";
        delete toDelete;
        return;
    }
    SongNode* temp = head;
    //to count if we have reached the desire node
    int count = 1;
    while (temp != NULL && count != pos) {
        //traversal ho rha ha
        temp = temp->next;
        count++;
    }
    //agr song nhi mila to invalid ha position
    if (temp == NULL) {
        cout << "\n\t\t\t   Invalid position! No song found to delete.\n";
        return;
    }
    //jo node k prev py song tha ab usko temp ki jaga temp->next ko point krwana ha
    temp->prev->next = temp->next;
    //temp agr last node nhi ha
    if (temp->next != NULL) {
    //temp k next ka jo prev which was basically temp ap uska connection khatam krna ha
    //is liye usk next k prev ma temp ka prev daal dyn gy
        temp->next->prev = temp->prev;
    }
    cout << "\n\t\t\t   Song '" << temp->title << "' deleted successfully! \n";
    delete temp;
}

void viewPlaylist(SongNode* head) {
    if (head == NULL) {
        cout << "\n\t\t\t   Playlist is empty! No songs to display.\n";
        return;
    }
    cout << "\n\t\t\t   Displaying the Playlist, here you go! \n";
    cout << "\t\t\t  ----------------------------------------\n";
    SongNode* temp = head;
    int count = 1;
    //tb tk traverse kryn gy jb tk sari list display na ho jaye
    while (temp != NULL) {
        cout << "\t\t\t   " << count++ << ". " << temp->title << endl;
        temp = temp->next;
    }
    cout << "\t\t\t  ----------------------------------------\n";
}

void shufflePlay(SongNode* head) {
    if (head == NULL) {
        cout << "\n\t\t\t   Playlist is empty! Cannot shuffle.\n";
        return;
    }

    int count = 0;
    SongNode* temp = head;
    //count kr rha k kitny songs hain playlist ma
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    //pointer to pointer ha aik alag node ha jo k point kry un sary songs ko jo playlist m hain
    SongNode** songs = new SongNode * [count];
    //sary traverse ho gaye thy is liye head kr diya
    temp = head;
    for (int i = 0; i < count; i++) {
        //sary songs add kr rhy hain songs
        songs[i] = temp;
        temp = temp->next;
    }

    for (int i = 0; i < count; i++) {
        //random index generate kr rhy hain
        int randIndex = rand() % count;
        //idhr udhr krny k liye
        SongNode* tempNode = songs[i];
        songs[i] = songs[randIndex];
        songs[randIndex] = tempNode;
    }
    //shuffled playlist ko display krwa do
    cout << "\n\t\t\t   Shuffled Playlist \n";
    cout << "\t\t\t  ----------------------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << "\t\t\t   " << i + 1 << ". " << songs[i]->title << endl;
    }
    cout << "\t\t\t  ----------------------------------------\n";

    delete[] songs;
}

void searchSong(SongNode* head, string songTitle) {
    SongNode* temp = head;
    int pos = 1;
    while (temp != NULL) {
        if (temp->title == songTitle) {
            cout << "\n\t\t\t   Song '" << songTitle << "' found at position: " << pos << "!\n";
            return;
        }
        temp = temp->next;
        pos++;
    }
    cout << "\n\t\t\t   Song '" << songTitle << "' not found in the playlist.\n";
}

void playRandomSong(SongNode* head) {
    if (head == NULL) {
        cout << "\n\t\t\t   Playlist is empty! Cannot play a random song.\n";
        return;
    }

    int count = 0;
    SongNode* temp = head;
    //kitny songs hain wo count kr rhy hain
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    //eg 5
    
    //random 12 % 5=2
    int randomIndex = rand() % count;
    //sary double linked list traverse kr liye tha yaani end node py thy to hm doobara usko head py la rhy hain
    temp = head;
    for (int i = 0; i < randomIndex; i++) {
        temp = temp->next;
        //2nd song tk
    }
    //2nd song play ho jaye ga
    cout << "\n\t\t\t   Now Playing: '" << temp->title << "' \n";
}

int main() {
    //playlist ko call kiya ha aur usko khaali rkha ha ta k user add kr dy songs
    SongNode* playlist = NULL;
    int choice;
    string title, afterTitle;
    int pos;

    do {
        cout << "\n\t\t\t========================================" << endl;
        cout << "\t\t\t           MUSIC PLAYLIST APP        " << endl;
        cout << "\t\t\t========================================" << endl;
        cout << "\t\t\t1. Add Song to Start\n\t\t\t2. Add Song to End\n\t\t\t3. Add Song After a Song\n";
        cout << "\t\t\t4. Delete Song\n\t\t\t5. View Playlist\n\t\t\t6. Shuffle Play\n\t\t\t7. Search Song\n\t\t\t8. Play Random Song\n\t\t\t9. Exit\n";
        cout << "\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\n\t\t\tEnter song title: ";
            cin.ignore();
            getline(cin, title);
            addSongToStart(playlist, title);
            break;
        case 2:
            cout << "\n\t\t\tEnter song title: ";
            cin.ignore();
            getline(cin, title);
            addSongToEnd(playlist, title);
            break;
        case 3:
            cout << "\n\t\t\tEnter the title of the song to add after: ";
            cin.ignore();
            getline(cin, afterTitle);
            cout << "\t\t\tEnter new song title: ";
            getline(cin, title);
            addSongAfter(playlist, afterTitle, title);
            break;
        case 4:
            cout << "\n\t\t\tEnter position to delete: ";
            cin >> pos;
            deleteSong(playlist, pos);
            break;
        case 5:
            viewPlaylist(playlist);
            break;
        case 6:
            shufflePlay(playlist);
            break;
        case 7:
            cout << "\n\t\t\tEnter song title to search: ";
            cin.ignore();
            getline(cin, title);
            searchSong(playlist, title);
            break;
        case 8:
            playRandomSong(playlist);
            break;
        case 9:
            cout << "\n\t\t\t   Exiting the app. Goodbye! \n";
            break;
        default:
            cout << "\n\t\t\t   Invalid choice! Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}

