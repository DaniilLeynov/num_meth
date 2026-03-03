import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv("errors.csv")

h = data["h"].values
log_h = np.log(h)

plt.figure()

orders = {
    "forward": 1,
    "central": 2,
    "second2": 2,
    "second4": 4
}

colors = {
    "forward": "red",
    "central": "green",
    "second2": "orange",
    "second4": "purple"
}

for column in data.columns[1:]:

    error = data[column].values
    log_error = np.log(error)
    color = colors[column];

    plt.plot(log_h, log_error, 'o-', color=color, label=f"{column} (num)")
    
    # teor line
    p = orders[column]

    C = log_error[0] - p * log_h[0]

    theoretical_line = p * log_h + C

    plt.plot(log_h, theoretical_line, '--', color=color,
             label=f"{column} (teor O(h^{p}))")

plt.xlabel("ln(h)")
plt.ylabel("ln(error)")
plt.legend()
plt.grid(True)
plt.show()
