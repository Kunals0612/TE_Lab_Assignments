import time
import random

# Disease rules with required symptoms
disease_rules = {
    "COVID-19": {"fever", "cough", "breathing_difficulty", "loss_of_taste_smell", "fatigue"},
    "Flu": {"fever", "cough", "fatigue", "body_ache", "headache"},
    "Common Cold": {"cough", "sore_throat", "runny_nose", "headache"},
    "Allergy": {"sneezing", "runny_nose", "itchy_eyes", "headache"},
    "Dengue": {"fever", "headache", "body_ache", "rash", "nausea"},
    "Malaria": {"fever", "chills", "sweating", "headache", "nausea"},
}

# Recommendations for each disease
recommendations = {
    "COVID-19": "Get tested and isolate yourself. Seek medical attention if symptoms worsen.",
    "Flu": "Rest well, drink fluids, and consult a doctor if needed.",
    "Common Cold": "Rest, stay warm, and drink plenty of fluids.",
    "Allergy": "Avoid allergens and consider using antihistamines.",
    "Dengue": "Consult a doctor immediately. Avoid painkillers like ibuprofen.",
    "Malaria": "Seek medical treatment promptly. Take prescribed antimalarial medicines.",
    "Unknown": "Symptoms unclear. Please consult a healthcare professional.",
}

# Function to get user symptoms
def get_symptoms():
    print("\nPlease answer the following questions (yes/no):\n")
    symptoms = []
    questions = {
        "fever": "Do you have a fever?",
        "cough": "Are you experiencing a cough?",
        "fatigue": "Do you feel unusually tired or fatigued?",
        "breathing_difficulty": "Are you having difficulty breathing?",
        "headache": "Do you have a headache?",
        "sore_throat": "Do you have a sore throat?",
        "runny_nose": "Do you have a runny nose?",
        "sneezing": "Are you sneezing frequently?",
        "itchy_eyes": "Do you have itchy or watery eyes?",
        "body_ache": "Are you feeling body aches?",
        "rash": "Do you have any skin rash?",
        "chills": "Are you experiencing chills?",
        "sweating": "Are you sweating excessively?",
        "nausea": "Do you feel nauseous or like vomiting?",
        "loss_of_taste_smell": "Have you lost your sense of taste or smell?",
    }
    for symptom, question in questions.items():
        ans = input(f"{question} ").strip().lower()
        if ans == "yes":
            symptoms.append(symptom)
    return symptoms

# Diagnosing based on matched symptoms
def diagnose(symptoms):
    best_match = "Unknown"
    max_matched = 0

    for disease, rule_symptoms in disease_rules.items():
        matches = set(symptoms) & rule_symptoms
        if len(matches) > max_matched:
            max_matched = len(matches)
            best_match = disease

    return best_match

# Main system
def main():
    print("=" * 60)
    print("\033[1;92m            Welcome to the Medical Expert System\033[0m")
    print("=" * 60)
    time.sleep(1)

    symptoms = get_symptoms()

    print("\nAnalyzing your symptoms, please wait...")
    time.sleep(2)

    disease = diagnose(symptoms)

    print("\n" + "-" * 60)
    print(f"Diagnosis Result : {disease}")
    print(f"Recommendation   : {recommendations.get(disease)}")
    print("-" * 60)

    # Random health tip
    tips = [
        "Tip: Stay hydrated and drink clean water.",
        "Tip: Wash your hands frequently with soap.",
        "Tip: Get enough sleep to boost your immunity.",
        "Tip: Avoid self-medication without consulting a doctor.",
        "Tip: Eat a balanced and nutritious diet.",
        "Tip: Use mosquito nets to avoid diseases like dengue and malaria.",
        "Tip: Avoid crowded places if you're feeling sick.",
    ]
    print(random.choice(tips))
    print("=" * 60)
    print("\033[1;91m 🔥 Note: This system is not a substitute for professional medical advice. 🔥\033[0m")
    print("=" * 60)

if __name__ == "__main__":
    main()