import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import random

data = pd.read_csv('Student Study Hour V2.csv')
test_data = pd.read_csv('test_data.csv')


class Model:
    m = None
    b = None
    alpha = None

    def __init__(self):
        self.m = 0
        self.b = 0
        self.alpha = 0.0001

    def init(self):
        self.m = random.random()
        self.b = random.random()
        self.alpha = random.uniform(0.0001, 0.00015)

    def loss(self, data):
        return squared_mean(self.m, self.b, data)

    def test(self, data):
        return squared_mean(self.m, self.b, data)

    def train(self, epochs, train_data):
        for i in range(epochs):
            if i % 2 == 0:
                print('#', end='')
            if i != 0 and i % 200 == 0:
                print('')
            self.m, self.b = gradient_descent(self.m, self.b, train_data, self.alpha)
            #print(f"m: #{self.m}, b: {self.b}")
        plt.scatter(data.Hours, data.Scores, color='black')
        plt.plot(list(range(0, 10)), [self.m * x + self.b for x in range(0, 10)], color='red')
        plt.show()


def gradient_descent(m_now, b_now, points, alpha):
    m_gradient = 0
    b_gradient = 0

    n = len(points)

    for i in range(n):
        x = points.iloc[i].Hours
        y = points.iloc[i].Scores

        m_gradient += -(2/n) * x * (y - (m_now * x + b_now))
        b_gradient += -(2/n) * (y - (m_now * x + b_now))
    
    m = m_now - m_gradient * alpha
    b = b_now - b_gradient * alpha

    return m, b


def squared_mean(m, b, points):
    total_error = 0
    for i in range(len(points)):
        x = points.iloc[i].Hours
        y = points.iloc[i].Scores
        total_error += (y - (m * x + b)) ** 2
    total_error /= float(len(points))
    return total_error


def main():
    model = Model()
    print(f"test loss: {model.test(test_data)}")
    model.train(2500, data)
    print(f"test loss: {model.test(test_data)}")


if __name__ == "__main__":
    main()


