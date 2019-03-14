bt = read.csv(file = "saida_bt.csv")
list = read.csv(file = "saida_list.csv")

par(las=1, cex = 1, bty = "l", tcl = -0.2, col="black", family="serif", mfrow = c(2,1), oma =  c(4,1,1,1))

plot(bt, xlab = "Tamanho", ylab = "Quantidade de comparações")  
plot(list, xlab = "Tamanho", ylab = "Quantidade de comparações")