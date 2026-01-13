import java.awt.*;
import javax.swing.*;
import java.util.*;

public class Driver {
	
	static double totalPrice = 0.0;
	static JLabel totalLabel;
	static boolean discountApplied = false;
	static DefaultListModel<String> orderModel;
	static JList<String> orderList;
	static java.util.List<Double> orderPrices = new ArrayList<>();

	public static void main(String[] args) {
		// Load and validate image
		ImageIcon originalIcon = new ImageIcon("BlueFlower.png");

		if (originalIcon.getIconWidth() == -1) {
			JOptionPane.showMessageDialog(null, "Image not found!", "Error", JOptionPane.ERROR_MESSAGE);
			return;
		}

		buildGUI(originalIcon);
	}

	static void buildGUI(ImageIcon originalIcon) {
		// Scale image
		Image scaledImage = originalIcon.getImage().getScaledInstance(100, 100, Image.SCALE_SMOOTH);
		ImageIcon scaledIcon = new ImageIcon(scaledImage);

		// Welcome label with image
		JLabel label = new JLabel("Welcome to the Party!", scaledIcon, JLabel.CENTER);
		label.setHorizontalTextPosition(JLabel.CENTER);
		label.setVerticalTextPosition(JLabel.BOTTOM);
		label.setFont(new Font("Georgia", Font.ITALIC, 18));

		// Checkout button
		JButton checkOut = new JButton("Checkout");
		checkOut.setFont(new Font("Comic Sans MS", Font.PLAIN, 18));
		checkOut.addActionListener(e -> {
			totalPrice = 0.0;
			totalLabel.setText("Total: $0.00");
			orderModel.clear();
			orderPrices.clear();
		});

		// Menu panel
		JPanel menuPanel = new JPanel();
		menuPanel.setLayout(new BoxLayout(menuPanel, BoxLayout.LINE_AXIS));
		menuPanel.setBackground(Color.WHITE);
		menuPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

		// Add food categories
		menuPanel.add(createCategoryPanel("Appetizers", new String[]{
			"Teriyaki Chicken", "Spicy Dumplings", "Egg Drop Soup", "Chips and Dip"
		}, new double[]{5.00, 3.33, 3.00, 1.50}));

		menuPanel.add(Box.createHorizontalStrut(30));
		menuPanel.add(createCategoryPanel("Main Course", new String[]{
			"Steak", "Salmon Filet", "Pizza", "Hamburger"
		}, new double[]{10.00, 12.50, 7.00, 5.00}));

		menuPanel.add(Box.createHorizontalStrut(30));
		menuPanel.add(createCategoryPanel("Desserts", new String[]{
			"Ice Cream", "Cupcakes", "Cheesecake", "Tiramisu"
		}, new double[]{3.50, 4.00, 5.00, 6.75}));

		menuPanel.add(Box.createHorizontalStrut(30));
		menuPanel.add(createCategoryPanel("Drinks", new String[]{
			"Margarita", "Lemon Soda", "Soda", "Amaretto Sour"
		}, new double[]{3.00, 2.75, 2.50, 6.00}));
		
		//Combo buttons panel
		
		

		// Order list
		orderModel = new DefaultListModel<>();
		orderList = new JList<>(orderModel);
		orderList.setFont(new Font("Comic Sans MS", Font.PLAIN, 14));
		orderList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		JScrollPane orderScrollPane = new JScrollPane(orderList);
		orderScrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		orderScrollPane.setBorder(BorderFactory.createTitledBorder("Your Order:"));
		orderScrollPane.setPreferredSize(new Dimension(200, 250));

		// Total label
		totalLabel = new JLabel("Total: $0.00");
		totalLabel.setFont(new Font("Comic Sans MS", Font.PLAIN, 18));
		totalLabel.setForeground(new Color(80, 40, 2));

		// Remove item button
		JButton removeItemBtn = new JButton("Remove Selected Item");
		removeItemBtn.setFont(new Font("Comic Sans MS", Font.PLAIN, 14));
		removeItemBtn.addActionListener(e -> {
			int index = orderList.getSelectedIndex();
			if (index != -1) {
				totalPrice -= orderPrices.get(index);
				orderModel.remove(index);
				orderPrices.remove(index);
				totalLabel.setText(String.format("Total: $%.2f", totalPrice));
			}
			
		});

		// Discount button
		JButton discountBtn = new JButton("Apply 10% Discount");
		discountBtn.setFont(new Font("Comic Sans MS", Font.PLAIN, 14));
		discountBtn.addActionListener(e -> {
			if (!discountApplied && totalPrice > 0) {
				totalPrice *= 0.9;
				totalLabel.setText(String.format("Total: $%.2f", totalPrice));
				discountApplied = true;
			}
		});

		// Bottom panel
		JPanel bottomPanel = new JPanel();
		bottomPanel.setLayout(new BoxLayout(bottomPanel, BoxLayout.Y_AXIS));
		bottomPanel.setBackground(new Color(245, 222, 179));
		bottomPanel.add(orderScrollPane);
		bottomPanel.add(Box.createVerticalStrut(10));
		bottomPanel.add(totalLabel);
		bottomPanel.add(Box.createVerticalStrut(10));
		bottomPanel.add(removeItemBtn);
		bottomPanel.add(Box.createVerticalStrut(10));
		bottomPanel.add(discountBtn);

		// Frame
		JFrame frame = new JFrame("Hannah Banana's Banquet");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(1200, 800);
		frame.setLayout(new BorderLayout());
		frame.getContentPane().setBackground(new Color(245, 222, 179));

		JPanel topPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
		topPanel.setBackground(new Color(245, 222, 179));
		topPanel.add(label);

		JPanel centerWrapper = new JPanel();
		centerWrapper.setLayout(new BoxLayout(centerWrapper, BoxLayout.Y_AXIS));
		centerWrapper.setBackground(new Color(245, 222, 179));
		centerWrapper.add(menuPanel);

		JScrollPane scrollPane = new JScrollPane(centerWrapper);
		scrollPane.setBorder(BorderFactory.createEmptyBorder());

		frame.add(topPanel, BorderLayout.NORTH);
		frame.add(scrollPane, BorderLayout.CENTER);
		frame.add(bottomPanel, BorderLayout.WEST);
		frame.add(checkOut, BorderLayout.SOUTH);

		frame.setLocationRelativeTo(null);
		frame.setVisible(true);
	}

	// Update order and total
	static void updateTotal(double amount, String itemName) {
		totalPrice += amount;
		totalLabel.setText(String.format("Total: $%.2f", totalPrice));
		orderModel.addElement(String.format("%s - $%.2f", itemName, amount));
		orderPrices.add(amount);
	}

	// Create menu section
	private static JPanel createCategoryPanel(String category, String[] items, double[] prices) {
		JPanel categoryPanel = new JPanel();
		categoryPanel.setLayout(new BoxLayout(categoryPanel, BoxLayout.Y_AXIS));
		categoryPanel.setBackground(new Color(245, 222, 179));

		JLabel categoryLabel = new JLabel(category);
		categoryLabel.setFont(new Font("Comic Sans MS", Font.PLAIN, 18));
		categoryLabel.setAlignmentX(Component.TOP_ALIGNMENT);
		categoryPanel.add(categoryLabel);

		for (int i = 0; i < items.length; i++) {
			String itemName = items[i];
			double price = prices[i];
			JButton itemButton = new JButton(itemName + " ($" + String.format("%.2f", price) + ")");
			itemButton.setAlignmentX(Component.TOP_ALIGNMENT);
			itemButton.addActionListener(e -> updateTotal(price, itemName));
			categoryPanel.add(Box.createVerticalStrut(5));
			categoryPanel.add(itemButton);
		}

		categoryPanel.setBorder(BorderFactory.createEmptyBorder());
		return categoryPanel;
	}
}

