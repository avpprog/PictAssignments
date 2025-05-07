"""
Simple Customer Service Chatbot using NLTK
"""
import nltk
import random
from nltk.stem import WordNetLemmatizer

# Download NLTK data
nltk.download('punkt', quiet=True)
nltk.download('wordnet', quiet=True)

# Intents for customer service
intents = {
    "greeting": {
        "patterns": ["hi", "hello", "hey", "greetings", "what's up", "howdy"],
        "responses": ["Hello! How can I help you today?", "Hi there! How can I assist you?"]
    },
    "goodbye": {
        "patterns": ["bye", "goodbye", "see you", "later", "quit", "exit"],
        "responses": ["Goodbye! Have a nice day!", "Thanks for chatting. Bye!"]
    },
    "products": {
        "patterns": ["products", "what do you sell", "what can I buy", "offerings", "services"],
        "responses": ["We sell electronics, clothing, and home goods. What are you looking for?", 
                     "Our products include smartphones, laptops, and accessories. What interests you?"]
    },
    "returns": {
        "patterns": ["return", "refund", "exchange", "money back"],
        "responses": ["You can return items within 30 days with receipt for a full refund.", 
                     "Our return policy allows exchanges and refunds within 30 days of purchase."]
    },
    "shipping": {
        "patterns": ["shipping", "delivery", "when will it arrive", "shipping time", "track order"],
        "responses": ["Standard shipping takes 3-5 business days.", 
                     "We offer standard (3-5 days) and express (1-2 days) shipping options."]
    },
    "contact": {
        "patterns": ["contact", "phone", "email", "customer service", "talk to human"],
        "responses": ["You can reach customer service at 1-800-123-4567 or support@example.com.",
                     "Our support team is available at support@example.com or call 1-800-123-4567."]
    },
    "hours": {
        "patterns": ["hours", "when are you open", "business hours", "store hours"],
        "responses": ["We're open Monday-Friday 9am-9pm, Saturday 10am-8pm, and Sunday 11am-6pm.",
                     "Our business hours are 9am-9pm weekdays, 10am-8pm Saturday, 11am-6pm Sunday."]
    }
}

class SimpleCustomerChatbot:
    def _init_(self):
        self.lemmatizer = WordNetLemmatizer()
        
    def preprocess(self, text):
        """Tokenize and lemmatize text"""
        tokens = nltk.word_tokenize(text.lower())
        return [self.lemmatizer.lemmatize(token) for token in tokens]
    
    def get_intent(self, message):
        """Find the most likely intent for the message"""
        message_tokens = set(self.preprocess(message))
        
        # Find best matching intent
        best_match = None
        highest_score = 0
        
        for intent, data in intents.items():
            score = 0
            for pattern in data["patterns"]:
                pattern_tokens = set(self.preprocess(pattern))
                # Count matching tokens
                matches = message_tokens.intersection(pattern_tokens)
                if matches:
                    # If exact pattern match, return immediately
                    if message.lower() == pattern.lower():
                        return intent
                    # Otherwise score by number of matching tokens
                    score += len(matches)
            
            if score > highest_score:
                highest_score = score
                best_match = intent
        
        # Return best match if above threshold, otherwise None
        return best_match if highest_score > 0 else None
    
    def respond(self, message):
        """Generate a response to the message"""
        intent = self.get_intent(message)
        
        if intent:
            return random.choice(intents[intent]["responses"])
        else:
            return "I'm not sure I understand. Could you please rephrase that?"

def main():
    """Run the chatbot interactively"""
    print("Simple Customer Service Chatbot")
    print("==============================")
    print("Type 'quit' to exit")
    
    chatbot = SimpleCustomerChatbot()
    
    while True:
        user_input = input("\nYou: ")
        if user_input.lower() in ['quit', 'exit', 'bye']:
            print("Chatbot: Goodbye!")
            break
        
        response = chatbot.respond(user_input)
        print(f"Chatbot: {response}")

if _name_ == "_main_":
    main()