import torch
import numpy as np
import torch.nn as nn
from torch.autograd import Variable
import matplotlib.pyplot as plt

epochs = 100000
batch_size = 10
rate = 0.1
momentum = 0.5
log_interval = 10

x_train = torch.from_numpy(np.genfromtxt('data/x.txt',delimiter=",",dtype=np.float32)).reshape(-1,1) / 6.28
x = x_train
x2 = x * x
x3 = x2 * x
x4 = x3 * x
x5 = x4 * x
xn = torch.cat((x, x2, x3, x4), 1)

y_train = torch.from_numpy(np.genfromtxt('data/y.txt',delimiter=",",dtype=np.float32)).reshape(-1,1)

x_test = torch.from_numpy(np.genfromtxt('data/x_.txt',delimiter=",",dtype=np.float32)).reshape(-1,1)
y_test = torch.from_numpy(np.genfromtxt('data/y_.txt',delimiter=",",dtype=np.float32)).reshape(-1,1)

class Net(nn.Module):
	def __init__(self):
		super(Net, self).__init__()
		self.fc1 = nn.Linear(4, 1)

	def forward(self, x):
		x = self.fc1(x)
		return x

model = Net()

optimizer = torch.optim.SGD(model.parameters(), lr=rate, momentum=momentum)

def train(epoch):
	x, y = Variable(xn), Variable(y_train)
	optimizer.zero_grad()
	out = model.forward(x)
	loss = nn.MSELoss()(out, y)
	loss.backward()
	optimizer.step()
	print('epoch {}, loss {}'.format(epoch,loss.item()))


#def test(epoch):

def plot():
	x = x_train.data.numpy()
	y = y_train.data.numpy()
	p = model.forward(Variable(xn)).data.numpy()
	plt.plot(x, y, 'go', label = 'from data', alpha = .5)
	plt.plot(x, p, label = 'prediction', alpha = .5)
	plt.legend()
	plt.show()

def main():
	for epoch in range(1, epochs + 1):
		train(epoch)
#		test(epoch)

	print(model.fc1.weight)
	print(model.fc1.bias)

	plot()
	
main()
