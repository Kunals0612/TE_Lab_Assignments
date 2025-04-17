import streamlit as st

st.title("Hospital Chatbot")

responses = {
    "hello": "Hi there! How can I help you?",
    "how are you": "I'm just a bot, but I'm doing great! How about you?",
    "name": "I'm a simple chatbot created using Streamlit!",
    "bye": "Goodbye! Have a great day!",
    "details": "Here are the hospital details:\nName: City Care Hospital\nLocation: 123 Main Street, Springfield\nContact Number: +1 234 567 890\nEmergency Helpline: 911",
    "working hours": "I am available 24/7 to assist you!",
    "pharmacy": "The nearest pharmacy is Springfield Pharmacy, located at 456 Elm Street.",
    "ambulance": "Yes, we provide ambulance services. Call +1 234 567 891 for emergency assistance.",
    "visiting hours": "Visiting hours are from 9 AM to 7 PM.",
    "book": "You can book an appointment by calling our reception at +1 234 567 892 or visiting our website.",
    "appointment":"You can book an appointment by calling our reception at +1 234 567 892 or visiting our website.",
    "doctors": "We have specialists in cardiology, orthopedics, and general medicine. Contact us for more details.",
    "insurance": "Yes, we accept most major insurance providers.",
    "services": "We offer general checkups, emergency services, diagnostics, and specialized treatments.",
    "emergency": "Yes, our emergency department is open 24/7.",
    "online": "Yes, you can access your medical reports via our patient portal.",
    "maternity": "Yes, we have a well-equipped maternity ward with experienced staff.",
    "parking": "We have a parking lot available at the hospital entrance.",
    "wheelchair": "Yes, our facility is fully wheelchair accessible.",
    "payment": "We accept cash, credit/debit cards, and online payments.",
    "contact": "You can contact customer service at +1 234 567 893.",
}

if "messages" not in st.session_state:
    st.session_state.messages = []

for message in reversed(st.session_state.messages):
    with st.chat_message(message["role"]):
        st.write(message["content"])

user_input = st.text_input("You:", "", key="user_input")

if user_input:
    st.session_state.messages.insert(0, {"role": "user", "content": user_input})
    with st.chat_message("user"):
        st.write(user_input)
    
    bot_response = "Sorry, I don't understand that."
    for key in responses:
        if key in user_input.lower():
            bot_response = responses[key]
            break
    
    st.session_state.messages.insert(0, {"role": "assistant", "content": bot_response})
    with st.chat_message("assistant"):
        st.write(bot_response)
