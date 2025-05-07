#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

struct EmployeeEvaluation {
    // Performance metrics
    float productivity_score;
    float quality_score;
    float attendance_rate;
    float goal_completion;
    float initiative_score;
    
    // Team metrics
    float collaboration_score;
    float communication_score;
    
    // Development metrics
    float skill_improvement;
    float learning_adaptability;
    
    // Role information
    int department;
    int role_level;
    int tenure_months;
    bool leadership_role;
};

const vector<string> departments = {
    "Sales", "Marketing", "Engineering", "Product", 
    "Customer Support", "Operations", "Human Resources", "Finance"
};

const vector<string> role_levels = {
    "Entry Level", "Junior", "Mid-Level", "Senior", "Lead/Manager", "Executive"
};

float get_numeric_input(const string& prompt, float min_val = 0, float max_val = 10) {
    float value;
    cout << prompt;
    while (!(cin >> value) || value < min_val || value > max_val) {
        cout << "Please enter a valid number between " << min_val << " and " << max_val << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

int get_category_input(const string& prompt, const vector<string>& options) {
    cout << prompt << endl;
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i+1 << ". " << options[i] << endl;
    }
    
    int choice;
    while (true) {
        cout << "Enter choice (1-" << options.size() << "): ";
        cin >> choice;
        if (choice >= 1 && choice <= static_cast<int>(options.size())) {
            return choice - 1;
        }
        cout << "Invalid choice. Please try again.\n";
    }
}

bool get_yes_no_input(const string& prompt) {
    char choice;
    cout << prompt << " (y/n): ";
    while (true) {
        cin >> choice;
        if (choice == 'y' || choice == 'Y') return true;
        if (choice == 'n' || choice == 'N') return false;
        cout << "Please enter 'y' or 'n': ";
    }
}

EmployeeEvaluation get_user_input() {
    EmployeeEvaluation eval;

    cout << "=== Employee Performance Metrics ===" << endl;
    eval.productivity_score = get_numeric_input("Rate productivity (1-10): ", 1, 10);
    eval.quality_score = get_numeric_input("Rate quality of work (1-10): ", 1, 10);
    eval.attendance_rate = get_numeric_input("Enter attendance rate (%): ", 0, 100);
    eval.goal_completion = get_numeric_input("Rate goal completion percentage (%): ", 0, 100);
    eval.initiative_score = get_numeric_input("Rate initiative/proactiveness (1-10): ", 1, 10);

    cout << "\n=== Team & Collaboration Metrics ===" << endl;
    eval.collaboration_score = get_numeric_input("Rate team collaboration (1-10): ", 1, 10);
    eval.communication_score = get_numeric_input("Rate communication effectiveness (1-10): ", 1, 10);

    cout << "\n=== Development & Growth Metrics ===" << endl;
    eval.skill_improvement = get_numeric_input("Rate skill improvement over evaluation period (1-10): ", 1, 10);
    eval.learning_adaptability = get_numeric_input("Rate learning & adaptability (1-10): ", 1, 10);

    cout << "\n=== Role Information ===" << endl;
    eval.department = get_category_input("Select department:", departments);
    eval.role_level = get_category_input("Select role level:", role_levels);
    eval.tenure_months = get_numeric_input("Enter tenure in months: ", 0, 600);
    eval.leadership_role = get_yes_no_input("Is this employee in a leadership role?");

    return eval;
}

void evaluate_employee(const EmployeeEvaluation& eval) {
    // Calculate different aspect scores
    float performance_score = (eval.productivity_score * 0.35) + 
                              (eval.quality_score * 0.35) + 
                              (eval.attendance_rate / 10) * 0.15 + 
                              (eval.goal_completion / 10) * 0.15;
    
    float team_score = (eval.collaboration_score * 0.5) + 
                       (eval.communication_score * 0.5);
    
    float growth_score = (eval.skill_improvement * 0.6) + 
                         (eval.learning_adaptability * 0.4);
    
    // Weight adjustment based on role level and tenure
    float role_factor = (eval.role_level + 1) / 3.0;
    float tenure_factor = min(1.0f, eval.tenure_months / 36.0f);
    
    // Leadership adjustment
    float leadership_factor = eval.leadership_role ? 1.2f : 1.0f;
    
    // Calculate weighted overall score
    float overall_score = ((performance_score * 0.5) + 
                         (team_score * 0.3) + 
                         (growth_score * 0.2)) * 
                         role_factor * 
                         (1 + (tenure_factor * 0.1)) * 
                         leadership_factor;
    
    // Normalize to 100-point scale
    overall_score = min(100.0f, max(0.0f, overall_score * 10));
    
    // Output results
    cout << "\n=== Evaluation Results ===" << endl;
    cout << "Performance Score: " << performance_score << "/10\n";
    cout << "Team Collaboration Score: " << team_score << "/10\n";
    cout << "Growth & Development Score: " << growth_score << "/10\n";
    cout << "Overall Performance Rating: " << overall_score << "/100\n\n";

    cout << "Detailed Assessment:\n";
    
    // Performance assessment
    if (performance_score < 5) {
        cout << "- Performance: Below expectations. Significant improvement needed in productivity and quality.\n";
    } else if (performance_score >= 5 && performance_score < 7) {
        cout << "- Performance: Meets basic expectations. Room for improvement in work quality and output.\n";
    } else if (performance_score >= 7 && performance_score < 9) {
        cout << "- Performance: Exceeds expectations. Consistently delivers high-quality work.\n";
    } else {
        cout << "- Performance: Outstanding. Exceptional productivity and work quality.\n";
    }
    
    // Goal assessment
    if (eval.goal_completion < 60) {
        cout << "- Goal Achievement: Failed to meet assigned objectives.\n";
    } else if (eval.goal_completion >= 60 && eval.goal_completion < 80) {
        cout << "- Goal Achievement: Met most objectives but fell short on some targets.\n";
    } else if (eval.goal_completion >= 80 && eval.goal_completion < 95) {
        cout << "- Goal Achievement: Successfully met all key objectives.\n";
    } else {
        cout << "- Goal Achievement: Exceeded targets and expectations.\n";
    }
    
    // Team contribution assessment
    if (team_score < 5) {
        cout << "- Team Contribution: Struggles with collaboration and communication.\n";
    } else if (team_score >= 5 && team_score < 7) {
        cout << "- Team Contribution: Works adequately with team members.\n";
    } else if (team_score >= 7 && team_score < 9) {
        cout << "- Team Contribution: Valuable team player who enhances group performance.\n";
    } else {
        cout << "- Team Contribution: Exceptional team player who elevates the entire team.\n";
    }
    
    // Growth assessment
    if (growth_score < 5) {
        cout << "- Professional Growth: Limited improvement in skills and adaptability.\n";
    } else if (growth_score >= 5 && growth_score < 7) {
        cout << "- Professional Growth: Shows steady development in role competencies.\n";
    } else if (growth_score >= 7 && growth_score < 9) {
        cout << "- Professional Growth: Significant skill development and adaptability.\n";
    } else {
        cout << "- Professional Growth: Exceptional learner with outstanding adaptability.\n";
    }
    
    // Department-specific feedback
    cout << "\nDepartment-Specific Insights:\n";
    switch (eval.department) {
        case 0: // Sales
            if (eval.productivity_score > 7) {
                cout << "- Strong sales performance indicates potential for higher targets.\n";
            }
            break;
        case 1: // Marketing
            if (eval.initiative_score > 7) {
                cout << "- Creative approach to marketing challenges noted.\n";
            }
            break;
        case 2: // Engineering
            if (eval.quality_score > 7) {
                cout << "- Technical excellence demonstrated in engineering tasks.\n";
            }
            break;
        case 3: // Product
            if (eval.collaboration_score > 7) {
                cout << "- Effective cross-functional collaboration enhances product development.\n";
            }
            break;
        case 4: // Customer Support
            if (eval.communication_score > 7) {
                cout << "- Strong customer communication skills contribute to high satisfaction.\n";
            }
            break;
        default:
            cout << "- Demonstrates key competencies relevant to departmental objectives.\n";
    }
    
    // Final recommendations
    cout << "\nFinal Recommendations:\n";
    if (overall_score >= 85) {
        cout << "- Outstanding performer. Consider for promotion or expanded responsibilities.\n";
        cout << "- Eligible for highest performance bonus tier.\n";
        cout << "- Identify leadership opportunities or special projects to further career growth.\n";
    } else if (overall_score >= 70 && overall_score < 85) {
        cout << "- Strong performer. Provide challenging assignments to maintain engagement.\n";
        cout << "- Eligible for performance bonus.\n";
        cout << "- Create development plan focused on areas of potential growth.\n";
    } else if (overall_score >= 55 && overall_score < 70) {
        cout << "- Satisfactory performer. Provide targeted feedback to improve specific areas.\n";
        cout << "- Consider skill development opportunities to increase effectiveness.\n";
    } else {
        cout << "- Performance improvement needed. Implement formal improvement plan.\n";
        cout << "- Schedule more frequent check-ins and provide additional support.\n";
        cout << "- Set clear expectations and specific goals for next evaluation period.\n";
    }
    
    // Development recommendations
    cout << "\nDevelopment Focus Areas:\n";
    vector<pair<string, float>> scores = {
        {"Productivity", eval.productivity_score},
        {"Work Quality", eval.quality_score},
        {"Attendance", eval.attendance_rate / 10},
        {"Goal Achievement", eval.goal_completion / 10},
        {"Initiative", eval.initiative_score},
        {"Team Collaboration", eval.collaboration_score},
        {"Communication", eval.communication_score},
        {"Skill Development", eval.skill_improvement},
        {"Adaptability", eval.learning_adaptability}
    };
    
    // Find lowest scores to recommend development areas
    sort(scores.begin(), scores.end(), 
         [](const pair<string, float>& a, const pair<string, float>& b) {
             return a.second < b.second;
         });
    
    cout << "Based on evaluation, focus on improving these areas:\n";
    for (int i = 0; i < min(3, (int)scores.size()); i++) {
        if (scores[i].second < 7) {
            cout << "- " << scores[i].first << endl;
        }
    }
}

int main() {
    cout << "Employee Performance Evaluation Expert System\n";
    cout << "---------------------------------------------\n";
    EmployeeEvaluation evaluation = get_user_input();
    evaluate_employee(evaluation);
    return 0;
}