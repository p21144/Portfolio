#include <iostream>
#include <random>
#include <functional>
using namespace std;

class MinHeap{//Κλάση για την heap_min
private:
    float *heap;
    int CurrentSize, MaxSize;
public:

    MinHeap(int MaxHeapSize){
        MaxSize = MaxHeapSize;//ορίζουμε το μέγιστο αριθμό της σωρού
        heap = new float[MaxSize + 1];//σωρός με την οποία θα επεξεργάζομαι τη heap_min
        CurrentSize = MaxSize;
    }
    ~MinHeap(){delete[] heap;}

    void Initialize(float a[])
    {// δεσμεύει τη heap_min στην heap
        delete [] heap;
        heap = a;
        //Σε αυτόν τον βρόχο θα ταξινομηθούν όλα τα στοιχεία ώστε η heap_min να γίνει σωρός ελαχίστων
        for (int i = MaxSize/2; i >= 1; i--) {
            float y = heap[i]; // η y περιέχει μια υπό-ριζα
            int c = 2*i; // η c περιέχει το αριστερό της φύλλο
            while (c <= MaxSize) {//Σε αυτόν τον βρόχο θα ταξινομηθούν όλα τα στοιχεία που είναι κάτω από τη ρίζα
                if (c < MaxSize && heap[c] > heap[c+1]) // Εδώ επιλέγεται το φύλλο με τη μικρότερη τιμή (αν υπάρχουν δύο φύλλα)
                    c++;
                if (y <= heap[c])// ελέγχουμε αν η υπό-ριζα είναι μικρότερη από το μικρότερο φύλλο της
                    break; // αν ναι, αποφεύγουμε να τους αλλάξουμε θέση
                //αν όχι:
                heap[c/2] = heap[c]; // η υπό-ριζα αλλάζει την τιμή του μικρότερου φύλλου
                c *= 2; // ετοιμάζουμε τον βρόχο για επανάληψη με νέα υπό-ριζα το μικρότερο φύλλο
            }
            // βάζουμε την αρχική τιμή της πρώτης υπό-ριζας στη θέση όπου όλα τα φύλα από κάτω της έχουν μεγαλύτερες τιμές
            heap[c/2] = y;
        }
    }

    float Extract()
    {// αφαιρεί και επιστρέφει το πρώτο στοιχείο της σωρού και ξανά-ταξινομεί τη σωρό
        float x;
        x = heap[1]; // το πρώτο στοιχείο
        // ξανά-ταξινόμηση της σωρού:
        float y = heap[CurrentSize--]; // η y περιέχει το τελευταίο στοιχείο από τη σωρό και η θέση του διαγράφεται
        // βρίσκουμε τη θέση για τη y στη σωρό
        int i = 1, // αρχικοποιούμαι τη i στην ρίζα της σωρού
        ci = 2; // αρχικοποιούμαι τη c στο αριστερό φύλλο της ρίζας
        while (ci <= CurrentSize) {//ο βρόχος θα τελειώσει αφού έχουμε επεξεργαστεί κάθε θέση στη σωρό
            if (ci < CurrentSize && heap[ci] > heap[ci+1])//Εδώ επιλέγεται το φύλλο με τη μικρότερη τιμή (αν υπάρχουν δύο φύλλα)
                ci++;
            //  ελέγχουμε αν η ριζα που έχουμε επιλέξει είναι μικρότερη από το μικρότερο φύλλο της
            if (y <= heap[ci])
                break; // αν ναι, αποφεύγουμε να τους αλλάξουμε θέση
            //αν όχι:
            heap[i] = heap[ci];  // η υπό-ριζα αλλάζει την τιμή του μικρότερου φύλλου
            i = ci;// ετοιμάζουμε τον βρόχο για επανάληψη με νέα ριζα το μικρότερο φύλλο
            ci *= 2; //και επιλέγουμε το δεξί φύλλο της νέας ρίζας
        }
        heap[i] = y;// βάζουμε την τιμή του τελευταίου στοιχείου στη θέση όπου όλα τα φύλα από κάτω της έχουν μεγαλύτερες τιμές
        return x;// επιστρέφουμε το στοιχείο που αφαιρέσαμε
    }

    void Insert(float x)
    {//Εισάγει την τιμή της μεταβλητής x στη σωρό
    //Βρίσκουμε τη θέση του x στη σωρό
        int i = ++CurrentSize;// αυξάνουμε το μέγεθος της σωρού και επιλέγουμε το τέλος της
        //μέχρι να φτάσουμε την κορυφή της σωρού ή μια ρίζα με μικρότερη τιμή από το x, επαναλαμβάνουμε
        while (i != 1 && x < heap[i/2]) {
            heap[i] = heap[i/2]; // βάζουμε την τιμή της ρίζας στο άδειο φύλλο
            i /= 2; //επιλέγουμε τη ρίζα του i
        }
        heap[i] = x;//βάζουμε το x στη θέση του
    }

};

class MaxHeap{//Κλάση για την heap_max
private:
    int CurrentSize, MaxSize;
    float *heap;
public:

    MaxHeap(int MaxHeapSize){
        MaxSize = MaxHeapSize;//ορίζουμε το μέγιστο αριθμό της σωρού
        heap = new float[MaxSize + 1];//σωρός με την οποία θα επεξεργάζομαι τη heap_max
        CurrentSize = MaxSize;
    }
    ~MaxHeap(){delete [] heap;}

    void Initialize(float a[])
    {// δεσμεύει τη heap_max στην heap
        delete [] heap;
        heap = a;
        //Σε αυτόν τον βρόχο θα ταξινομηθούν όλα τα στοιχεία ώστε η heap_max να γίνει σωρός ελαχίστων
        for (int i = MaxSize/2; i >= 1; i--) {
            float y = heap[i];// η y περιέχει μια υπό-ριζα
            int c = 2*i; // η c περιέχει το αριστερό της φύλλο
            while (c <= MaxSize) {//Σε αυτόν τον βρόχο θα ταξινομηθούν όλα τα στοιχεία που είναι κάτω από τη ρίζα
                if (c < MaxSize && heap[c] < heap[c+1])
                    // Εδώ επιλέγεται το φύλλο με τη μεγαλύτερη τιμή (αν υπάρχουν δύο φύλλα)
                    c++;
                if (y >= heap[c])// ελέγχουμε αν η υπό-ριζα είναι μεγαλύτερη από το μεγαλύτερο φύλλο της
                    break; // αν ναι, αποφεύγουμε να τους αλλάξουμε θέση
                //αν όχι:
                heap[c/2] = heap[c]; // η υπό-ριζα αλλάζει την τιμή του μεγαλύτερου φύλλου
                c *= 2;  // ετοιμάζουμε τον βρόχο για επανάληψη με νέα υπό-ριζα το μεγαλύτερο φύλλο
            }
            // βάζουμε την αρχική τιμή της πρώτης υπό-ριζας στη θέση όπου όλα τα φύλα από κάτω της έχουν μικρότερες τιμές
            heap[c/2] = y;
        }
    }

    float Extract()
    {// αφαιρεί και επιστρέφει το πρώτο στοιχείο της σωρού και ξανά-ταξινομεί τη σωρό
        float x;
        x = heap[1]; //το x περιέχει το πρώτο στοιχείο
        // ξανά-ταξινόμηση της σωρού:
        float y = heap[CurrentSize--]; //η y περιέχει το τελευταίο στοιχείο από τη σωρό και η θέση του διαγράφεται
        // βρίσκουμε τη θέση της y στη σωρό
        int i = 1, // αρχικοποιούμαι τη i στη ρίζα της σωρού
        ci = 2; // αρχικοποιούμαι τη c στο αριστερό φύλλο της ρίζας
        while (ci <= CurrentSize) {//ο βρόχος θα τελειώσει αφού έχουμε επεξεργαστεί κάθε θέση στη σωρό
            if (ci < CurrentSize && heap[ci] < heap[ci+1])
                //Εδώ επιλέγεται το φύλλο με τη μεγαλύτερη τιμή (αν υπάρχουν δύο φύλλα)
                ci++;
            //  ελέγχουμε αν η ρίζα που έχουμε επιλέξει είναι μεγαλύτερη από το μεγαλύτερο φύλλο της
            if (y >= heap[ci])
                break; // αν ναι, αποφεύγουμε να τους αλλάξουμε θέση
            //αν όχι:
            heap[i] = heap[ci];// η υπό-ριζα αλλάζει την τιμή του μεγαλύτερου φύλλου
            i = ci;// ετοιμάζουμε τον βρόχο για επανάληψη με νέα ριζα το μεγαλύτερο φύλλο
            ci *= 2; //και επιλέγουμε το δεξί φύλλο της νέας ρίζας
        }
        heap[i] = y;// βάζουμε την τιμή του τελευταίου στοιχείου στη θέση όπου όλα τα φύλα από κάτω της έχουν μικρότερες τιμές
        return x;// επιστρέφουμε το στοιχείο που αφαιρέσαμε
    }

    void Insert(float x)
    {//Εισάγει την τιμή της μεταβλητής x στη σωρό
        //Βρίσκουμε τη θέση του x στη σωρό
        int i = ++CurrentSize;// αυξάνουμε το μέγεθος της σωρού και επιλέγουμε το τέλος της
        //μέχρι να φτάσουμε την κορυφή της σωρού ή μια ρίζα με μεγαλύτερη τιμή από το x, επαναλαμβάνουμε
        while (i != 1 && x > heap[i/2]) {
            heap[i] = heap[i/2];// βάζουμε την τιμή της ρίζας στο άδειο φύλλο
            i /= 2; //επιλέγουμε τη ρίζα του i
        }
        heap[i] = x;//βάζουμε το x στη θέση του
    }

};

int main() {
    //Αρχικοποιούμαι τη μεταβλητή Ν
    int N;
    cout << "Enter Array's size" << endl;
    cin >> N;
    //Αρχικοποιούμαι τον πίνακα heap_min με Ν τυχαία στοιχεία
    default_random_engine generator;
    chi_squared_distribution<float> my_distribution(0.5);
    auto random_num = bind(my_distribution, generator);
    float *heap_min = new float[N+1];
    for (int i = 1; i <= N; i++)
        //δεν δίνουμε τιμή στο heap_min[0] για μεγαλύτερη ευκολία όταν επεξεργαζόμαστε τις θέσεις του πίνακα
        heap_min[i] = random_num() * 10000.0;
    //Αρχικοποιούμαι τον πίνακα heap_max με τα στοιχεία του heap_min
    float *heap_max = new float[N+1];
    for (int i = 1; i <= N; i++)
        heap_max[i] = heap_min[i];

    //μετατρέπουμε την heap_min σε σωρό ελαχίστων
    MinHeap min(N);
    min.Initialize(heap_min);
    //Εξάγουμε τα δύο μικρότερα στοιχεία, τα προσθέτουμε και το αποτέλεσμα το εισάγουμε στην heap_min
    //Αυτό επαναλαμβάνεται μέχρι να προστεθούν όλα τα στοιχεία της heap_min
    //όπου το άθροισμα θα είναι στην θέση heap_min[1]
    for (int i = 1; i < N; i++)
        min.Insert(min.Extract() + min.Extract());
    cout << "The sum, always starting from the smallest numbers is: " << heap_min[1];
    //μετατρέπουμε την heap_max σε σωρό μεγίστων
    MaxHeap max(N);
    max.Initialize(heap_max);
    //Εξάγουμε τα δύο μεγαλύτερα στοιχεία, τα προσθέτουμε και το αποτέλεσμα το εισάγουμε στην heap_max
    //Αυτό επαναλαμβάνεται μέχρι να προστεθούν όλα τα στοιχεία της heap_max
    //όπου το άθροισμα θα είναι στην θέση heap_max[1]
    for (int i = 1; i < N; i++)
        max.Insert(max.Extract() + max.Extract());
    cout << "\nThe sum, always starting from the largest numbers is: " << heap_max[1];

    return 0;
}