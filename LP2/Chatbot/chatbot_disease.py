import streamlit as st
import nltk
from nltk.stem import WordNetLemmatizer
import random

# Download necessary NLTK data
nltk.download('punkt')
nltk.download('wordnet')

lemmatizer = WordNetLemmatizer()

# Symptom-to-condition map (simple for demo purposes)
disease_db = {
    
    "cold": ["sneezing", "runny nose", "cough", "sore throat"],
    "flu": ["fever", "chills", "body ache", "fatigue", "cough"],
    "covid-19": ["fever", "dry cough", "loss of taste", "loss of smell", "breathing difficulty"],
    "malaria": ["fever", "chills", "sweating", "nausea", "vomiting"],
    "migraine": ["headache", "nausea", "sensitivity to light", "aura", "vomiting"]
}

responses = {
   
    "cold": "You might have a common cold. Stay warm and rest.",
    "flu": "Sounds like the flu. Make sure to stay hydrated.",
    "covid-19": "These symptoms match COVID-19. Please consider getting tested.",
    "malaria": "Symptoms suggest malaria. Please seek immediate medical help.",
    "migraine": "You may be experiencing a migraine. Try resting in a dark, quiet room.",
    "unknown": "I'm not sure about the condition. It's best to consult a doctor."
}

def lemmatize_input(text):
    tokens = nltk.word_tokenize(text.lower())
    return [lemmatizer.lemmatize(token) for token in tokens]

def diagnose(symptoms):
    match_counts = {}
    for condition, keywords in disease_db.items():
        match = len(set(symptoms) & set([lemmatizer.lemmatize(word) for word in keywords]))
        match_counts[condition] = match
    
    best_match = max(match_counts, key=match_counts.get)
    return best_match if match_counts[best_match] > 0 else "unknown"

# Streamlit UI
st.set_page_config(page_title="🩺 Symptom Checker Bot", page_icon="💬")
st.title("💬 Health Symptom Checker Chatbot")

st.markdown("Enter your symptoms (e.g., 'fever, cough, sore throat'):")

if "chat" not in st.session_state:
    st.session_state.chat = []

user_input = st.text_input("You:", key="user_input")

if st.button("Check") and user_input:
    lemmatized = lemmatize_input(user_input)
    condition = diagnose(lemmatized)
    response = responses.get(condition, responses["unknown"])

    st.session_state.chat.append(("You", user_input))
    st.session_state.chat.append(("Bot", response + " ⚠️ Please consult a healthcare professional."))

# Display conversation
for sender, message in st.session_state.chat:
    st.markdown(f"**{sender}:** {message}")
