import gradio as gr
from nltk.chat.util import Chat, reflections

pairs = [
    # Greetings
    [r"hi|hello|hey", ["Hello! Welcome to HotelBot. How can I assist you today?"]],
    [r"how are you", ["I'm doing great! How can I help you with your hotel needs?"]],
    
    # Book Room
    [r"(.*)book(.*)room(.*)", ["To book a room, you can visit our website or call us at 123-456-7890. How can I assist you further?"]],
    [r"(.*)reservation(.*)", ["You can make a reservation online through our website or give us a call at 123-456-7890. What else would you like to know?"]],
    
    # Menu
    [r"(.*)menu(.*)", ["Our menu includes continental breakfast, sandwiches, soups, and salads. What would you like to order?"]],
    [r"(.*)food(.*)", ["We offer a variety of meals including breakfast, lunch, and dinner. What would you like to have?"]],
    
    # Hours
    [r"(.*)hours(.*)", ["Our hotel is open 24/7 to serve you. How can I assist you further?"]],
    [r"(.*)open(.*)", ["We are open 24/7. Let me know if you need anything else."]],
    
    # Location
    [r"(.*)location(.*)", ["Our hotel is located at 123 Main Street, City, State, ZIP. How can I help you further?"]],
    [r"(.*)address(.*)", ["We are situated at 123 Main Street, City, State, ZIP. What else would you like to know?"]],
    
    # Contact
    [r"(.*)contact(.*)", ["You can contact us at 123-456-7890 or email us at info@hotel.com. How can I assist you further?"]],
    [r"(.*)phone(.*)", ["You can reach us at 123-456-7890. What else would you like to know?"]],
    
    # Exit
    [r"exit|bye|quit", ["Goodbye! Thank you for visiting HotelBot. Have a great day!"]],
    
    # Fallback
    [r"(.*)", ["Sorry, I didn't understand that. Can you rephrase your question or ask about booking, menu, hours, location, etc.?"]],
]

chatbot = Chat(pairs, reflections)

def respond(messgae,history):
    return chatbot.respond(messgae)

demo = gr.ChatInterface(
    fn = respond,
    title = "HotelBot",
    description = "Book room and food",
    theme="soft"
)
demo.launch()