#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For formatting money output

using namespace std;

// --- DATA STRUCTURES ---

// Represents an Insurance Policy
struct Policy {
    int id;
    string holderName;
    string policyType; // e.g., "Gold", "Silver"
    double maxCoverageLimit;
    bool isActive;
};

// Represents a Claim submitted by a user
struct Claim {
    int claimId;
    int policyId;
    double amount;
    string status; // "Pending", "Approved", "Rejected"
    string reason; // Why it was rejected or approved
};

// --- GLOBAL STORAGE (Simulating a Database) ---
vector<Policy> policies;
vector<Claim> claims;
int nextPolicyId = 101;
int nextClaimId = 501;

// --- FUNCTION: Rule-Based Validation Module ---
// This satisfies the requirement: "Rule-based validation module"
string validateClaim(Policy& p, double amount) {
    // Rule 1: Policy must be active
    if (!p.isActive) return "REJECTED: Policy is inactive.";
    
    // Rule 2: Claim amount cannot exceed policy limit
    if (amount > p.maxCoverageLimit) return "REJECTED: Amount exceeds coverage limit.";
    
    // Rule 3: Minimum claim amount check (Business Logic)
    if (amount <= 0) return "REJECTED: Invalid amount.";

    return "APPROVED";
}

// --- FEATURE: Policy Management ---
void addPolicy() {
    Policy p;
    p.id = nextPolicyId++;
    cout << "Enter Holder Name: "; cin >> p.holderName;
    cout << "Enter Policy Type (Gold/Silver): "; cin >> p.policyType;
    cout << "Enter Max Coverage Limit ($): "; cin >> p.maxCoverageLimit;
    p.isActive = true;
    
    policies.push_back(p);
    cout << ">> Policy Created Successfully! ID: " << p.id << endl;
}

// --- FEATURE: Claim Submission ---
void submitClaim() {
    int pId;
    double amt;
    cout << "Enter Policy ID to claim against: "; cin >> pId;
    cout << "Enter Claim Amount: "; cin >> amt;

    // Check if policy exists
    bool found = false;
    for(auto& p : policies) {
        if(p.id == pId) {
            found = true;
            Claim c;
            c.claimId = nextClaimId++;
            c.policyId = pId;
            c.amount = amt;
            c.status = "Pending";
            c.reason = "Waiting for processing";
            claims.push_back(c);
            cout << ">> Claim Submitted Successfully! Claim ID: " << c.claimId << endl;
            break;
        }
    }
    if(!found) cout << ">> Error: Policy ID not found." << endl;
}

// --- FEATURE: Automation & Processing ---
void processAllClaims() {
    cout << "\n--- Processing Claims (Automation Running)... ---\n";
    int processedCount = 0;

    for(auto& c : claims) {
        if(c.status == "Pending") {
            // Find the associated policy
            for(auto& p : policies) {
                if(p.id == c.policyId) {
                    // Apply Rules
                    string result = validateClaim(p, c.amount);
                    
                    if(result == "APPROVED") {
                        c.status = "Approved";
                        c.reason = "Within limits and policy active.";
                    } else {
                        c.status = "Rejected";
                        c.reason = result;
                    }
                    processedCount++;
                }
            }
        }
    }
    cout << ">> Processing Complete. " << processedCount << " claims evaluated." << endl;
}

// --- FEATURE: Reports ---
void showReports() {
    cout << "\n=== CLAIM PROCESSING REPORT ===" << endl;
    cout << left << setw(10) << "ClaimID" << setw(10) << "PolID" << setw(10) << "Amount" << setw(12) << "Status" << "Reason" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    
    for(const auto& c : claims) {
        cout << left << setw(10) << c.claimId 
             << setw(10) << c.policyId 
             << setw(10) << "$" << c.amount 
             << setw(12) << c.status 
             << c.reason << endl;
    }
    cout << "---------------------------------" << endl;
}

// --- MAIN MENU ---
int main() {
    int choice;
    while(true) {
        cout << "\n=== HEALTH INSURANCE SYSTEM (C++) ===" << endl;
        cout << "1. Add New Policy" << endl;
        cout << "2. Submit New Claim" << endl;
        cout << "3. Process Claims (Run Automation)" << endl;
        cout << "4. View Reports" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose option: ";
        cin >> choice;

        if(choice == 1) addPolicy();
        else if(choice == 2) submitClaim();
        else if(choice == 3) processAllClaims();
        else if(choice == 4) showReports();
        else if(choice == 5) break;
        else cout << "Invalid option!" << endl;
    }
    return 0;
}