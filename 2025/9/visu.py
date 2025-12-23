import matplotlib.pyplot as plt


guess_x = [5207, 94634, 94634, 5207, 5207]
guess_y =  [66267, 66267, 50282, 50282, 66267]

# Read the data
with open('input.txt', 'r') as f:
    points = [line.strip().split(',') for line in f]
    x_coords = [int(p[0]) for p in points]
    y_coords = [int(p[1]) for p in points]

# Create the plot
plt.figure(figsize=(12, 8))
#plt.plot(x_coords, y_coords)
plt.plot(x_coords, y_coords)
plt.plot(guess_x, guess_y)
plt.xlabel('X')
plt.ylabel('Y')
plt.title('X,Y Coordinates Visualization')
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.show()


