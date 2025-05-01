from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
from nltk.corpus import wordnet
import numpy as np
import re
import nltk

nltk.download('wordnet')

# Step 1: Define expanded FAQ (20 questions)
faq = {
    "What courses do you offer?": "We offer undergraduate and postgraduate programs in science, arts, and technology.",
    "How do I apply for admission?": "You can apply online through our admissions portal.",
    "What is the fee structure?": "The fee structure varies by course. Visit our website for detailed information.",
    "Where is the campus located?": "Our main campus is in New Delhi, India.",
    "How can I contact the admission office?": "Contact us at admissions@example.edu.",
    "Do you offer scholarships?": "Yes, we offer merit-based and need-based scholarships.",
    "What are the eligibility criteria for undergraduate courses?": "You must have passed 10+2 or equivalent with required subjects.",
    "What documents are needed for admission?": "You need academic transcripts, ID proof, and a passport-size photo.",
    "When does the academic year begin?": "Our academic year begins in August.",
    "Do you provide hostel facilities?": "Yes, separate hostels are available for boys and girls.",
    "What is the last date to apply?": "The deadline for applications is usually in May.",
    "Is there an entrance exam?": "Yes, most courses require a written entrance test.",
    "What postgraduate programs do you have?": "We offer MBA, M.Sc, M.A, and M.Tech programs.",
    "Are international students accepted?": "Yes, we welcome students from all over the world.",
    "What is the mode of teaching?": "We follow a blended mode of classroom and online learning.",
    "How can I track my application status?": "Log into the admission portal to check your status.",
    "Do you offer part-time courses?": "Yes, we have part-time programs for working professionals.",
    "What are the career services available?": "We have a dedicated placement and career counseling cell.",
    "Can I visit the campus before applying?": "Yes, campus tours are organized every Friday.",
    "Are online courses available?": "Yes, we offer several certified online courses."
}

# Step 2: Define domain-specific important keywords
important_keywords = [
    "admission", "apply", "course", "fee", "location", "contact", "scholarship",
    "eligibility", "documents", "academic", "hostel", "deadline", "exam", "international",
    "teaching", "application", "part-time", "career", "campus", "online"
]

# Step 3: Build a synonym map
def get_synonyms(word):
    synonyms = set()
    for syn in wordnet.synsets(word):
        for lemma in syn.lemmas():
            synonyms.add(lemma.name().replace("_", " "))
    return list(synonyms)

def build_synonym_map(keywords):
    synonym_map = {}
    for key in keywords:
        base = key.split()[0]
        syns = get_synonyms(base)
        synonym_map[key] = set(syns)
        synonym_map[key].add(key)
    reverse_map = {}
    for canonical, syns in synonym_map.items():
        for s in syns:
            reverse_map[s.lower()] = canonical
    return reverse_map

reverse_synonyms = build_synonym_map(important_keywords)

# Step 4: Normalize input using synonym map
def normalize_question(text):
    text = text.lower()
    for syn, canonical in reverse_synonyms.items():
        pattern = r'\b' + re.escape(syn) + r'\b'
        text = re.sub(pattern, canonical, text)
    return text

# Step 5: TF-IDF setup
questions = list(faq.keys())
vectorizer = TfidfVectorizer()
normalized_questions = [normalize_question(q) for q in questions]
tfidf_matrix = vectorizer.fit_transform(normalized_questions)

# Step 6: Chat loop
print("Welcome to the Education InfoBot! Type 'exit' to quit.")
while True:
    user_question = input("You: ")
    if user_question.lower() == 'exit':
        print("Chatbot: Goodbye!")
        break

    normalized_input = normalize_question(user_question)
    user_vec = vectorizer.transform([normalized_input])
    similarity = cosine_similarity(user_vec, tfidf_matrix)

    best_match_idx = np.argmax(similarity)
    best_score = similarity[0][best_match_idx]

    if best_score < 0.3:
        print("Chatbot: Sorry, I don't understand your question.")
    else:
        matched_question = questions[best_match_idx]
        print("Chatbot:", faq[matched_question])
