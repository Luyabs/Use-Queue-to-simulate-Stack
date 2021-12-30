import matplotlib.pyplot as plt
import math

def drawpic1():
    with open("data1.txt") as data1:
        lines = data1.readlines()

    x_set = [8 + i * 40.0784 for i in range(0,103)]    #横轴 表示 2^i 数据规模     (3,17)表示8~65536
    y_set = []                          #原始纵轴 表示运算时间
    ydivx_set = [[],[],[]]              #纵轴 运算时间/数据数量

    for line in lines:
        linestr = line.strip('\n')
        linestrlist = (linestr.split(" "))
        linestrlist = list(map(float, linestrlist))
        y_set.append(linestrlist)
    
    for i in range(0,3):
        scale = 1024
        for time in y_set[i]:
            temp = time / scale
            scale += 40.88
            ydivx_set[i].append(temp)

    print(x_set)
    print(y_set)
    print(ydivx_set)

    #fig , ax = plt.subplots(nrows=2, ncols=2)

    plt.scatter(x_set, y_set[0], s = 30, marker='p', label="switch")
    plt.scatter(x_set, y_set[1], s = 30, marker='p', label="merge")
    plt.scatter(x_set, y_set[2], s = 30, marker='p', label="merge_neo")
    plt.title(r'Push Compare', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Push Compare.jpg")
    plt.show()
    plt.close()

    plt.scatter(x_set, ydivx_set[0], s = 30, marker='p', label="switch")
    plt.scatter(x_set, ydivx_set[1], s = 30, marker='p', label="merge")
    plt.scatter(x_set, ydivx_set[2], s = 30, marker='p', label="merge_neo")
    plt.title(r'Push Compare Processed', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/datasize /s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Push Compare Processed.jpg")
    plt.show()
    plt.close()

    plt.plot(x_set, y_set[0], linewidth = 3, label="switch")
    plt.plot(x_set, y_set[1], linewidth = 3, label="merge")
    plt.plot(x_set, y_set[2], linewidth = 3, label="merge_neo")
    plt.title(r'Push Compare', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time /s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Push Compare2.jpg")
    plt.show()
    plt.close()

    plt.plot(x_set, ydivx_set[0], linewidth = 3, label="switch")
    plt.plot(x_set, ydivx_set[1], linewidth = 3, label="merge")
    plt.plot(x_set, ydivx_set[2], linewidth = 3, label="merge_neo")
    plt.title(r'Push Compare Processed', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/datasize /s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Push Compare Processed2.jpg")
    plt.show()
    plt.close()

def drawpic1_revise():
    with open("data1.txt") as data1:
        lines = data1.readlines()

    x_set = [8 + i * 40.0784 for i in range(0,103)]    #横轴 表示 2^i 数据规模     (3,17)表示8~65536
    y_set = []                          #原始纵轴 表示运算时间
    ydivx_set = [[],[],[]]              #纵轴 运算时间/数据数量

    for line in lines:
        linestr = line.strip('\n')
        linestrlist = (linestr.split(" "))
        linestrlist = list(map(float, linestrlist))
        y_set.append(linestrlist)
    
    for i in range(0,3):
        scale = 1024
        for time in y_set[i]:
            temp = time / scale
            scale += 40.88
            ydivx_set[i].append(temp)

    print(x_set)
    print(y_set)
    print(ydivx_set)

    #plt.scatter(x_set, y_set[0], s = 30, marker='p', label="switch")
    plt.scatter(x_set, y_set[2], s = 30, marker='p', label="merge_neo")
    plt.scatter(x_set, y_set[1], s = 30, marker='p', label="merge")
    plt.title(r'Push Compare', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    #plt.savefig("Push Compare4.jpg")
    plt.show()
    plt.close()

    #plt.scatter(x_set, ydivx_set[0], s = 30, marker='p', label="switch")
    plt.scatter(x_set, ydivx_set[2], s = 180, marker='p', label="merge_neo")
    plt.scatter(x_set, ydivx_set[1], s = 180, marker='p', label="merge")
    plt.title(r'Push Compare Processed', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/datasize /s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    #plt.savefig("Push Compare Processed4.jpg")
    plt.show()
    plt.close()

   # plt.plot(x_set, y_set[0], linewidth = 3)
    plt.plot(x_set, y_set[2], linewidth = 3, label="merge_neo")
    plt.plot(x_set, y_set[1], linewidth = 3, label="merge")
    plt.title(r'Push Compare', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time /s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    #plt.savefig("Push Compare3.jpg")
    plt.show()
    plt.close()

    #plt.plot(x_set, ydivx_set[0], linewidth = 3)
    plt.plot(x_set, ydivx_set[2], linewidth = 15, label="merge_neo")
    plt.plot(x_set, ydivx_set[1], linewidth = 15, label="merge")
    plt.title(r'Push Compare Processed', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/datasize /s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Push Compare Processed3.jpg")
    plt.show()
    plt.close()

def drawpic2():
    with open("data2.txt") as data2:
        lines = data2.readlines()

    x_set = [128 + i * 654.08 for i in range(0,101)]    #横轴 表示 2^i 数据规模     (3,17)表示8~65536
    y_set = []                          #原始纵轴 表示运算时间
    ydivx_set = [[],[]]              #纵轴 运算时间/数据数量

    for line in lines:
        linestr = line.strip('\n')
        linestrlist = (linestr.split(" "))
        linestrlist = list(map(float, linestrlist))
        y_set.append(linestrlist)
    
    for i in range(0,2):
        scale = 128
        for time in y_set[i]:
            temp = time / scale
            scale += 654.08
            ydivx_set[i].append(temp)

    print(x_set)
    print(y_set)
    print(ydivx_set)

    plt.scatter(x_set, y_set[1], s = 30, marker='p', label="merge_neo")
    plt.scatter(x_set, y_set[0], s = 30, marker='p', label="merge")
    plt.title(r'Merge Compare', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Merge Compare.jpg")
    plt.show()
    plt.close()

    plt.scatter(x_set, ydivx_set[1], s = 30, marker='p', label="merge_neo")
    plt.scatter(x_set, ydivx_set[0], s = 30, marker='p', label="merge")
    plt.title(r'Merge Compare Processed', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/datasize /s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Merge Compare Processed.jpg")
    plt.show()
    plt.close()

    plt.plot(x_set, y_set[1], linewidth = 3, label="merge_neo")
    plt.plot(x_set, y_set[0], linewidth = 3, label="merge")
    plt.title(r'Merge Compare', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Merge Compare2.jpg")
    plt.show()
    plt.close()

    plt.plot(x_set, ydivx_set[1], linewidth = 3, label="merge_neo")
    plt.plot(x_set, ydivx_set[0], linewidth = 3, label="merge")
    plt.title(r'Merge Compare Processed', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/datasize /s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Merge Compare Processed2.jpg")
    plt.show()
    plt.close()

def drawpic3():
    with open("data3.txt") as data3:
        lines = data3.readlines()

    x_set = [1024 + i * 317.44 for i in range(0,101)]    #横轴 表示 2^i 数据规模     (3,17)表示8~65536
    y_set = []                          #原始纵轴 表示运算时间
    ydivx_set = [[],[],[],[],[],[]]              #纵轴 运算时间/数据数量

    for line in lines:
        linestr = line.strip('\n')
        linestrlist = (linestr.split(" "))
        linestrlist = list(map(float, linestrlist))
        y_set.append(linestrlist)
    
    for i in range(0,6):
        scale = 1024
        for time in y_set[i]:
            temp = time / scale
            scale += 317.44
            ydivx_set[i].append(temp)

    print(x_set)
    print(y_set)
    print(ydivx_set)

    plt.scatter(x_set, y_set[0], s = 15, marker='p', label="8")
    plt.scatter(x_set, y_set[1], s = 15, marker='p', label="256")
    plt.scatter(x_set, y_set[2], s = 15, marker='p', label="512")
    plt.scatter(x_set, y_set[3], s = 15, marker='p', label="1024")
    plt.scatter(x_set, y_set[4], s = 15, marker='p', label="2048")
    plt.scatter(x_set, y_set[5], s = 15, marker='p', label="4096")
    plt.title(r'Original Data Compare', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Original Data Compare.jpg")
    plt.show()
    plt.close()

    plt.scatter(x_set, ydivx_set[0], s = 15, marker='p', label="8")
    plt.scatter(x_set, ydivx_set[1], s = 15, marker='p', label="256")
    plt.scatter(x_set, ydivx_set[2], s = 15, marker='p', label="512")
    plt.scatter(x_set, ydivx_set[3], s = 15, marker='p', label="1024")
    plt.scatter(x_set, ydivx_set[4], s = 15, marker='p', label="2048")
    plt.scatter(x_set, ydivx_set[5], s = 15, marker='p', label="4096")
    plt.title(r'Original Data Compare Processed', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/datasize /s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Original Data Compare Processed.jpg")
    plt.show()
    plt.close()

    plt.plot(x_set, y_set[0], linewidth = 3, label="8")
    plt.plot(x_set, y_set[1], linewidth = 3, label="256")
    plt.plot(x_set, y_set[2], linewidth = 3, label="512")
    plt.plot(x_set, y_set[3], linewidth = 3, label="1024")
    plt.plot(x_set, y_set[4], linewidth = 3, label="2048")
    plt.plot(x_set, y_set[5], linewidth = 3, label="4096")
    plt.title(r'Original Data Compare', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Original Data Compare2.jpg")
    plt.show()
    plt.close()

    plt.plot(x_set, ydivx_set[0], linewidth = 3, label="8")
    plt.plot(x_set, ydivx_set[1], linewidth = 3, label="256")
    plt.plot(x_set, ydivx_set[2], linewidth = 3, label="512")
    plt.plot(x_set, ydivx_set[3], linewidth = 3, label="1024")
    plt.plot(x_set, ydivx_set[4], linewidth = 3, label="2048")
    plt.plot(x_set, ydivx_set[5], linewidth = 3, label="4096")
    plt.title(r'Original Data Compare Processed', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/datasize /s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Original Data Compare Processed2.jpg")
    plt.show()
    plt.close()

def drawpic4():
    with open("data4.txt") as data4:
        lines = data4.readlines()

    x_set = [2 ** i for i in range(3,18)]    #横轴 表示 2^i 数据规模     (3,17)表示8~65536
    y_set = []                          #原始纵轴 表示运算时间
    ydivx_set = [[],[]]              #纵轴 运算时间/数据数量

    for line in lines:
        linestr = line.strip('\n')
        linestrlist = (linestr.split(" "))
        linestrlist = list(map(float, linestrlist))
        y_set.append(linestrlist)
    
    for i in range(0,2):
        scale = 8
        for time in y_set[i]:
            temp = time / scale
            scale *= 2
            ydivx_set[i].append(temp)

    print(x_set)
    print(y_set)
    print(ydivx_set)

    plt.scatter(x_set, y_set[1], s = 30, marker='p', label="merge_neo")
    plt.scatter(x_set, y_set[0], s = 30, marker='p', label="merge")
    plt.title(r'Merge Compare', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Merge Compare3.jpg")
    plt.show()
    plt.close()

    plt.scatter(x_set, ydivx_set[1], s = 30, marker='p', label="merge_neo")
    plt.scatter(x_set, ydivx_set[0], s = 30, marker='p', label="merge")
    plt.title(r'Merge Compare Processed', fontsize=22)
    plt.xlabel('data size', fontsize=22)                      #坐标
    plt.ylabel('time/datasize /s', fontsize=22)
    plt.grid()                              #网格
    plt.legend(loc='best', fontsize=16)
    plt.savefig("Merge Compare Processed3.jpg")
    plt.show()
    plt.close()

    plt.plot(x_set, y_set[0], linewidth = 3)
    plt.plot(x_set, y_set[1], linewidth = 3)
    plt.show()
    plt.close()

    plt.plot(x_set, ydivx_set[0], linewidth = 3)
    plt.plot(x_set, ydivx_set[1], linewidth = 3)
    plt.show()
    plt.close()

    plt.show()
    plt.close()

drawpic1()
drawpic1_revise()
drawpic2()
drawpic3()
drawpic4()


'''
import tensorflow as tf
from tensorflow import keras
import matplotlib.pyplot as plt

model = keras.models.Sequential([
    keras.layers.Flatten(1),
    keras.layers.Dense(10, kernel_initializer="he_normal"),
    keras.layers.LeakyReLU(),
    keras.layers.Dense(1)
])

model.compile(loss="sparse_categorical_crossentropy",
              optimizer=keras.optimizers.SGD(learning_rate=0.2),
              metrics=["accuracy"])

mdoel.fit(x, y, epochs=10)

plt.ion()   # something about plotting

for t in range(0,400):
    if t % 5 == 0:          #每5步更新一次
        # plot and show learning process
        plt.cla()
        plt.scatter(x.data.numpy(), y.data.numpy())
        plt.plot(x.data.numpy(), prediction.data.numpy(), 'r-', lw=5)
        plt.text(0.5, 0, 'Loss=%.4f' % loss.data.numpy(), fontdict={'size': 20, 'color':  'red'})
        plt.pause(0.1)

plt.ioff()
plt.show()
'''
