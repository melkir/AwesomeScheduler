/*
   main.cpp

   Test application for the multithreaded work queue in C++.
  
   ------------------------------------------

   Copyright @ 2013 [Vic Hargrave - http://vichargrave.com]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <zconf.h>
#include "threads/thread.h"
#include "wqueue.h"

class WorkItem {
    //m_message->proc m_number->profil
    string proc;
    int profil;
    string in;
    string out;
    int disk;
    int power;
    int cputime;

public:
    WorkItem(const char *proc, int profil, char *in, char *out, int disk, int power, int cputime)
            : proc(proc), profil(profil), in(in), out(out), disk(disk), power(power), cputime(cputime) { }

    ~WorkItem() { }

    const char *getProc() { return proc.c_str(); }

    int getProfil() { return profil; }

    const char *getIn() { return in.c_str(); }

    const char *getOut() { return out.c_str(); }

    int getDisk() { return disk; }

    int getPower() { return power; }

    int getCputime() { return cputime; }
};

class ConsumerThread : public Thread {
    wqueue<WorkItem *> &m_queue;

public:
    ConsumerThread(wqueue<WorkItem *> &queue) : m_queue(queue) { }

    void *run() {
        // Remove 1 item at a time and process it. Blocks if no items are 
        // available to process.
        for (int i = 0; ; i++) {
            printf("threads %lu, loop %d - waiting for item...\n",
                   (long unsigned int) self(), i);
            WorkItem *item = m_queue.remove();
            printf("threads %lu, loop %d - got one item\n",
                   (long unsigned int) self(), i);
            printf("threads %lu, loop %d - item: proc - %s, profil - %d, in - %s, out - %s, disk - %i, power - %i, cputime - %i\n",
                   (long unsigned int) self(), i,
                   item->getProc(),
                   item->getProfil(),
                   item->getIn(),
                   item->getOut(),
                   item->getDisk(),
                   item->getPower(),
                   item->getCputime());
            delete item;
        }
        return NULL;
    }
};

int main(int argc, char **argv) {
    // Process command line arguments
    if (argc % 7 != 1) {
        printf("usage: %s <iterations>\n", argv[0]);
        exit(-1);
    }
    //int iterations = atoi(argv[1]);

    // Create the queue and consumer (worker) threads
    wqueue<WorkItem *> queue;
    ConsumerThread *thread1 = new ConsumerThread(queue);
    ConsumerThread *thread2 = new ConsumerThread(queue);
    thread1->start();
    thread2->start();

    // Add items to the queue
/*    WorkItem* item;
    for (int i = 0; i < iterations; i++) {
        item = new WorkItem("abc", 123);
        queue.add(item);
        item = new WorkItem("def", 456);
        queue.add(item);
        item = new WorkItem("ghi", 789);
        queue.add(item);
        sleep(1);
    }
 */

    //---------------debut tentative--------

    WorkItem *item;
    int size = (argc + 1) / 7;
    for (int i = 1; i <= size + 1; i = i + 2) {
        item = new WorkItem(argv[i],
                            atoi(argv[i+1]),
                            argv[i+2],
                            argv[i+3],
                            atoi(argv[i+4]),
                            atoi(argv[i+5]),
                            atoi(argv[i+6]));
        queue.add(item);
        sleep(1);
    }

    //--------------end---------------------

    // Wait for the queue to be empty
    while (queue.size() < 0);
    printf("done\n");
    exit(0);
}
