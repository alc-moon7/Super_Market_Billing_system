document.addEventListener('DOMContentLoaded', function() {
    // Menu navigation
    const menuButtons = document.querySelectorAll('.menu-btn');
    const contentSections = document.querySelectorAll('.content-section');
    
    menuButtons.forEach(button => {
        button.addEventListener('click', function() {
            // Remove active class from all buttons and sections
            menuButtons.forEach(btn => btn.classList.remove('active'));
            contentSections.forEach(section => section.classList.remove('active'));
            
            // Add active class to clicked button and corresponding section
            this.classList.add('active');
            const sectionId = this.getAttribute('data-section');
            document.getElementById(sectionId).classList.add('active');
        });
    });

    // Terminal simulation
    const terminalOutput = document.getElementById('terminal-output');
    const commandInput = document.getElementById('command-input');
    const cartItems = document.getElementById('cart-items');
    const cartTotal = document.getElementById('cart-total');
    
    let cart = [];
    
    commandInput.addEventListener('keypress', function(e) {
        if (e.key === 'Enter') {
            const command = this.value.trim();
            this.value = '';
            
            // Add command to terminal output
            terminalOutput.innerHTML += `<p>> ${command}</p>`;
            
            // Process command
            processCommand(command);
            
            // Scroll to bottom of terminal
            terminalOutput.scrollTop = terminalOutput.scrollHeight;
        }
    });
    
    function processCommand(command) {
        switch(command) {
            case '1':
                addItemToCart();
                break;
            case '2':
                generateBill();
                break;
            case '3':
                viewCart();
                break;
            case '4':
                cancelItem();
                break;
            case '5':
                terminalOutput.innerHTML += '<p>> Thank you for using our system. Goodbye!</p>';
                break;
            default:
                terminalOutput.innerHTML += '<p>> Invalid option. Please try again.</p>';
        }
    }
    
    function addItemToCart() {
        // In a real implementation, you would prompt for item details
        const itemId = Math.floor(Math.random() * 1000);
        const items = [
            { name: "Milk", price: 2.99 },
            { name: "Bread", price: 1.99 },
            { name: "Eggs", price: 3.49 },
            { name: "Apples", price: 0.99 },
            { name: "Chicken", price: 5.99 }
        ];
        const randomItem = items[Math.floor(Math.random() * items.length)];
        const quantity = Math.floor(Math.random() * 5) + 1;
        
        const item = {
            id: itemId,
            name: randomItem.name,
            price: randomItem.price,
            quantity: quantity
        };
        
        cart.push(item);
        updateCartDisplay();
        terminalOutput.innerHTML += `<p>> Added ${quantity} ${randomItem.name}(s) at $${randomItem.price.toFixed(2)} each</p>`;
    }
    
    function generateBill() {
        if (cart.length === 0) {
            terminalOutput.innerHTML += '<p>> Cart is empty. No bill generated.</p>';
            return;
        }
        
        let billText = '>> ====== BILL ======\n';
        let total = 0;
        
        cart.forEach(item => {
            const itemTotal = item.price * item.quantity;
            total += itemTotal;
            billText += `>> ${item.name} x ${item.quantity}: $${itemTotal.toFixed(2)}\n`;
        });
        
        billText += `>> -----------------\n>> TOTAL: $${total.toFixed(2)}\n>> =================`;
        
        terminalOutput.innerHTML += `<p>${billText.replace(/\n/g, '<br>')}</p>`;
        
        // Clear cart after generating bill
        cart = [];
        updateCartDisplay();
    }
    
    function viewCart() {
        if (cart.length === 0) {
            terminalOutput.innerHTML += '<p>> Your cart is empty.</p>';
            return;
        }
        
        let cartText = '>> ====== CART ======\n';
        let total = 0;
        
        cart.forEach(item => {
            const itemTotal = item.price * item.quantity;
            total += itemTotal;
            cartText += `>> ${item.name} x ${item.quantity}: $${itemTotal.toFixed(2)}\n`;
        });
        
        cartText += `>> -----------------\n>> TOTAL: $${total.toFixed(2)}\n>> =================`;
        
        terminalOutput.innerHTML += `<p>${cartText.replace(/\n/g, '<br>')}</p>`;
    }
    
    function cancelItem() {
        if (cart.length === 0) {
            terminalOutput.innerHTML += '<p>> Your cart is empty. Nothing to cancel.</p>';
            return;
        }
        
        // In a real implementation, you would prompt for which item to cancel
        const removedItem = cart.pop();
        updateCartDisplay();
        terminalOutput.innerHTML += `<p>> Removed ${removedItem.quantity} ${removedItem.name}(s) from cart</p>`;
    }
    
    function updateCartDisplay() {
        cartItems.innerHTML = '';
        let total = 0;
        
        if (cart.length === 0) {
            cartItems.innerHTML = '<p class="empty-cart">Your cart is empty</p>';
            cartTotal.textContent = '$0.00';
            return;
        }
        
        cart.forEach(item => {
            const itemElement = document.createElement('div');
            itemElement.className = 'cart-item';
            
            const itemTotal = item.price * item.quantity;
            total += itemTotal;
            
            itemElement.innerHTML = `
                <span>${item.name} x ${item.quantity}</span>
                <span>$${itemTotal.toFixed(2)}</span>
            `;
            
            cartItems.appendChild(itemElement);
        });
        
        cartTotal.textContent = `$${total.toFixed(2)}`;
    }
    
    // Initialize with empty cart
    updateCartDisplay();
});