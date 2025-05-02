import streamlit as st
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
from nltk.corpus import wordnet
import numpy as np
import re
import nltk

nltk.download('wordnet')

# Expanded general-purpose FAQ
faq = {
    "What services do you offer?": "We offer a wide range of customer solutions including 24/7 support.",
    "How can I contact customer support?": "You can reach us at support@example.com or call 1800-000-000.",
    "Where are you located?": "Our headquarters is in New York, with offices worldwide.",
    "Do you offer refunds?": "Yes, our refund policy lasts 30 days from the date of purchase.",
    "Can I track my order?": "Yes, use the tracking ID provided in your order confirmation email.",
    "How long does shipping take?": "Shipping typically takes 3–7 business days depending on your location.",
    "What payment methods do you accept?": "We accept credit/debit cards, PayPal, and digital wallets.",
    "How do I reset my password?": "Click on 'Forgot Password' on the login page and follow the instructions.",
    "Can I change or cancel my order?": "Yes, within 24 hours of placing the order. Contact support for help.",
    "Is there a mobile app available?": "Yes, download our app from the App Store or Google Play.",
    "Do you have international shipping?": "Yes, we ship to over 100 countries worldwide.",
    "What if I received a damaged product?": "Please contact support with photos within 48 hours of delivery.",
    "Can I update my shipping address after ordering?": "Yes, but only before the order is shipped.",
    "Are there any ongoing promotions?": "Visit our website's offers section for current discounts.",
    "How do I subscribe to your newsletter?": "Enter your email at the bottom of our homepage to subscribe.",
    "Do you provide bulk or enterprise discounts?": "Yes, contact our sales team for custom pricing.",
    "How secure is my personal data?": "We use encryption and secure protocols to protect all user data.",
    "Can I get an invoice for my purchase?": "Yes, invoices are emailed automatically after purchase.",
    "Do you offer customer loyalty rewards?": "Yes, earn points for every purchase and redeem them later.",
    "What are your business hours?": "Our support team is available Monday to Friday, 9 AM to 6 PM EST."
}

# General-purpose keywords
important_keywords = [
    "services", "contact", "location", "refund", "order", "support", "track", "purchase", "payment",
    "shipping", "password", "cancel", "app", "international", "damaged", "address", "promotions",
    "newsletter", "discounts", "security", "invoice", "loyalty", "hours"
]

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

def normalize_question(text):
    text = text.lower()
    for syn, canonical in reverse_synonyms.items():
        pattern = r'\b' + re.escape(syn) + r'\b'
        text = re.sub(pattern, canonical, text)
    return text

questions = list(faq.keys())
normalized_questions = [normalize_question(q) for q in questions]
vectorizer = TfidfVectorizer()
tfidf_matrix = vectorizer.fit_transform(normalized_questions)

# Streamlit UI
st.set_page_config(page_title="Customer InfoBot", page_icon="💬")
st.title("💬 Customer InfoBot")
st.write("Ask me anything about services, orders, policies, or support.")

user_input = st.text_input("You:", "")

if user_input:
    normalized_input = normalize_question(user_input)
    user_vec = vectorizer.transform([normalized_input])
    similarity = cosine_similarity(user_vec, tfidf_matrix)

    best_match_idx = np.argmax(similarity)
    best_score = similarity[0][best_match_idx]

    if best_score < 0.3:
        st.error("🤖 Bot: Sorry, I didn't quite get that. Could you rephrase?")
    else:
        matched_question = questions[best_match_idx]
        st.success(f"🤖 Bot: {faq[matched_question]}")
