bt = read.csv(file = "saida_bt.csv")
list = read.csv(file = "saida_list.csv")

comparison_bt = bt$comparison
size_bt = bt$size

comparison_list = list$comparison
size_list = list$size

par(las=1, cex = 1, bty = "l", tcl = -0.2, col="black", family="serif", mfrow = c(2,1), oma =  c(1,1,1,1))

plot(comparison_bt~size_bt, xlab = "Tamanho", ylab = "Quantidade de comparações")  
plot(comparison_list~size_list, xlab = "Tamanho", ylab = "Quantidade de comparações")  
