#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

// Function to simulate LRU page replacement algorithm
int lruPageReplacement(const vector<int>& pages, int numFrames) {
    unordered_map<int, int> pageLastUsed; // Map to store the index of the last use of each page
    vector<int> frames; // Frames to store pages in memory
    int pageFaults = 0; // Counter for page faults

    cout << "For LRU Algorithm:" << endl;

    // Iterate through the page reference string
    for (int i = 0; i < pages.size(); ++i) {
        cout << "Step " << i + 1 << ": ";

        // Check if the page is not already in frames
        if (find(frames.begin(), frames.end(), pages[i]) == frames.end()) {
            // If frames are not full, add the page directly
            if (frames.size() < numFrames) {
                frames.push_back(pages[i]);
            }
            else {
                // If frames are full, find the least recently used page to replace
                int leastRecentlyUsedPage = frames[0];
                for (int j = 1; j < numFrames; ++j) {
                    if (pageLastUsed[frames[j]] < pageLastUsed[leastRecentlyUsedPage]) {
                        leastRecentlyUsedPage = frames[j];
                    }
                }
                auto it = find(frames.begin(), frames.end(), leastRecentlyUsedPage);
                *it = pages[i];
            }
            // Increment page fault counter
            pageFaults++;
            cout << "Page fault (" << pages[i] << ") - Page Table: {";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "}, Frames: [";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "], Faults: " << pageFaults << endl;
        }
        else {
            // If page is already in frames, no page fault occurs
            cout << "No page fault - Page Table: {";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "}, Frames: [";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "], Faults: " << pageFaults << endl;
        }
        // Update the index of last use for the current page
        pageLastUsed[pages[i]] = i;
    }

    cout << "Total Page Faults: " << pageFaults << endl << endl;
    return pageFaults;
}

// Function to simulate Optimal page replacement algorithm
int optimalPageReplacement(const vector<int>& pages, int numFrames) {
    unordered_map<int, int> nextPageIndex; // Map to store the index of next occurrence of each page
    vector<int> frames; // Frames to store pages in memory
    int pageFaults = 0; // Counter for page faults

    cout << "For Optimal Algorithm:" << endl;

    // Iterate through the page reference string
    for (int i = 0; i < pages.size(); ++i) {
        cout << "Step " << i + 1 << ": ";

        // Check if the page is not already in frames
        if (find(frames.begin(), frames.end(), pages[i]) == frames.end()) {
            // If frames are not full, add the page directly
            if (frames.size() < numFrames) {
                frames.push_back(pages[i]);
            }
            else {
                // If frames are full, find the page with farthest next use to replace
                int farthestNextUseIndex = -1;
                int pageToRemove;
                for (int j = 0; j < frames.size(); ++j) {
                    // If a page is not found in the future reference string, remove it
                    if (nextPageIndex.find(frames[j]) == nextPageIndex.end()) {
                        pageToRemove = frames[j];
                        break;
                    }
                    // Update the page with the farthest next use
                    if (nextPageIndex[frames[j]] > farthestNextUseIndex) {
                        farthestNextUseIndex = nextPageIndex[frames[j]];
                        pageToRemove = frames[j];
                    }
                }
                auto it = find(frames.begin(), frames.end(), pageToRemove);
                *it = pages[i];
            }
            // Increment page fault counter
            pageFaults++;
            cout << "Page fault (" << pages[i] << ") - Page Table: {";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "}, Frames: [";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "], Faults: " << pageFaults << endl;
        }
        else {
            // If page is already in frames, no page fault occurs
            cout << "No page fault - Page Table: {";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "}, Frames: [";
            for (int j = 0; j < frames.size(); ++j) {
                cout << frames[j];
                if (j != frames.size() - 1) cout << ", ";
            }
            cout << "], Faults: " << pageFaults << endl;
        }
        // Update the index of next occurrence for each page
        nextPageIndex[pages[i]] = i + 1;
    }

    cout << "Total Page Faults: " << pageFaults << endl << endl;
    return pageFaults;
}

// Function to simulate FIFO page replacement algorithm
int fifoPageReplacement(const vector<int>& pages, int numFrames) {
    queue<int> frameQueue; // Queue to store frames in FIFO order
    unordered_map<int, bool> inFrames; // Map to keep track of whether a page is in frames
    int pageFaults = 0; // Counter for page faults

    cout << "For FIFO Algorithm:" << endl;

    // Iterate through the page reference string
    for (int i = 0; i < pages.size(); ++i) {
        cout << "Step " << i + 1 << ": ";

        // Check if the page is not already in frames
        if (!inFrames[pages[i]]) {
            // If frames are full, remove the oldest page
            if (frameQueue.size() == numFrames) {
                int oldestPage = frameQueue.front();
                frameQueue.pop();
                inFrames[oldestPage] = false;
            }
            // Add the new page to frames
            frameQueue.push(pages[i]);
            inFrames[pages[i]] = true;
            // Increment page fault counter
            pageFaults++;
            cout << "Page fault (" << pages[i] << ") - Page Table: {";
            queue<int> tempQueue = frameQueue;
            while (!tempQueue.empty()) {
                cout << tempQueue.front();
                tempQueue.pop();
                if (!tempQueue.empty()) cout << ", ";
            }
            cout << "}, Frames: [";
            tempQueue = frameQueue;
            while (!tempQueue.empty()) {
                cout << tempQueue.front();
                tempQueue.pop();
                if (!tempQueue.empty()) cout << ", ";
            }
            cout << "], Faults: " << pageFaults << endl;
        }
        else {
            // If page is already in frames, no page fault occurs
            cout << "No page fault - Page Table: {";
            queue<int> tempQueue = frameQueue;
            while (!tempQueue.empty()) {
                cout << tempQueue.front();
                tempQueue.pop();
                if (!tempQueue.empty()) cout << ", ";
            }
            cout << "}, Frames: [";
            tempQueue = frameQueue;
            while (!tempQueue.empty()) {
                cout << tempQueue.front();
                tempQueue.pop();
                if (!tempQueue.empty()) cout << ", ";
            }
            cout << "], Faults: " << pageFaults << endl;
        }
    }

    cout << "Total Page Faults: " << pageFaults << endl << endl;
    return pageFaults;
}

int main() {
    // Sample input
    vector<int> pageReferenceString = { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 };
    int numFrames = 4;

    // Output for LRU Algorithm
    lruPageReplacement(pageReferenceString, numFrames);

    // Output for Optimal Algorithm
    optimalPageReplacement(pageReferenceString, numFrames);

    // Output for FIFO Algorithm
    fifoPageReplacement(pageReferenceString, numFrames);

    return 0;
}
