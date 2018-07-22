from __future__ import print_function
import numpy as np
import os
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torchvision import datasets, transforms, utils as U
from torch.autograd import Variable
from collections import OrderedDict

epochs = 10
batch_size = 50
rate = 0.01
momentum = 0.5
log_interval = 10

torch.manual_seed(42)

print('===> Loading data')

train_dataset = datasets.MNIST(
	root='data',
	train=True,
	download=True,
	transform=transforms.Compose([
		transforms.Resize((32, 32)),
		transforms.ToTensor()])
)

test_dataset = datasets.MNIST(
	root='data', 
	train=False,
	transform=transforms.Compose([
		transforms.Resize((32, 32)),
		transforms.ToTensor()])
)

train_loader = torch.utils.data.DataLoader(
	dataset=train_dataset, 
	batch_size=batch_size, 
	shuffle=True)

test_loader = torch.utils.data.DataLoader(
	dataset=test_dataset, 
	batch_size=batch_size, 
	shuffle=False)

print('===> Building model')
class LeNet5(nn.Module):
	def __init__(self):
		super(LeNet5, self).__init__()
		
		self.po = nn.MaxPool2d(kernel_size=(2, 2), stride=2)

		self.c1 = nn.Conv2d(1, 6, kernel_size=(5, 5))
		self.c2 = nn.Conv2d(6, 16, kernel_size=(5, 5))
		self.c3 = nn.Conv2d(16, 120, kernel_size=(5, 5))

		self.l1 = nn.Linear(120, 84)
		self.l2 = nn.Linear(84, 10)

		self.convnet = nn.Sequential(
			self.c1,
			nn.ReLU(),
			self.po,
			self.c2,
			nn.ReLU(),
			self.po,
			self.c3,
			nn.ReLU()
		)

		self.fc = nn.Sequential(
			nn.Linear(120, 84),
			nn.ReLU(),
			nn.Linear(84, 10)
		)

	def forward(self, x):
		x = self.convnet(x)
		x = x.view(-1, 120)
		x = self.fc(x)
		x = F.log_softmax(x, dim=1)
		return x

model = LeNet5()

optimizer = optim.Adam(model.parameters(), lr=rate)

def train(epoch):
	model.train()
	samples_seen = 0
	for data, target in train_loader:
		data, target = Variable(data), Variable(target)
		optimizer.zero_grad()
		output = model(data)
		loss = F.cross_entropy(output, target)
		loss.backward()
		optimizer.step()
		samples_seen += data.size(0)
		if (samples_seen // data.size(0)) % log_interval == 0:
			print('Train Epoch: {} [{}/{} ({:.0f}%)]\tLoss: {:.6f}'.format(
				epoch, samples_seen, len(train_loader.dataset),
				100. * samples_seen / len(train_loader.dataset), loss.item()))

def test(epoch):
	model.eval()
	test_loss = 0
	correct = 0
	for data, target in test_loader:
		with torch.no_grad():
			data = Variable(data)
		target = Variable(target)
		output = model(data)
		test_loss += F.nll_loss(output, target).item()
		pred = output.data.max(1)[1] # get the index of the max log-probability
		correct += pred.eq(target.data).cpu().sum()

	test_loss = test_loss
	test_loss /= len(test_loader) # loss function already averages over batch size
	print('\nTest set: Average loss: {:.4f}, Accuracy: {}/{} ({:.0f}%)\n'.format(
		test_loss, correct, len(test_loader.dataset),
		100. * correct / len(test_loader.dataset)))

def createFolder(directory):
	if not os.path.exists(directory):
		os.makedirs(directory)

def main():
	print(model.c1.weight.size())
	print(model.c2.weight.size())
	print(model.c3.weight.size())
	print(model.l1.weight.size())
	print(model.l2.weight.size())

	for epoch in range(1, epochs + 1):
		train(epoch)
		test(epoch)
		folder = 'data/' + "{:04d}/".format(epoch)
		createFolder(folder)
	
		x = test_dataset.__getitem__(epoch)[0].reshape(-1, 1, 32, 32)
		U.save_image(x, folder + 'x.bmp', 1, 0, True)
		convolved = model.convnet(x)
		U.save_image(convolved.reshape(-1, 1, 10, 12), folder + 'convolved.bmp', 6, 0, True)

		y = F.relu(model.fc(convolved.reshape(-1, 120)).reshape(-1))
		y = y / y.sum()
		np.savetxt(folder + 'y.csv', y.detach().numpy(), fmt='%.6f')

		U.save_image(model.c1.weight, folder + 'c1.bmp', 6, 1, True)
		U.save_image(model.c2.weight.reshape(-1, 1, 5, 5), folder + 'c2.bmp', 6, 1, True)
		U.save_image(model.c3.weight.reshape(-1, 1, 5, 5), folder + 'c3.bmp', 16, 1, True)
		U.save_image(model.l1.weight.reshape(-1, 1, 84, 120), folder + 'l1.bmp', 1, 0, True)
		U.save_image(model.l2.weight.reshape(-1, 1, 10, 84), folder + 'l2.bmp', 1, 0, True)

main()
