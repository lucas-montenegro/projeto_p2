setwd("diretorio_a_ser_inserido")
par(las=1, cex = 1, bty = "l", tcl = -0.2, col="black", family="serif")#caso seja necessario plotar dois gráficos, mfrow=c(1,2))
test <- read.csv("nome_do_arquivo.csv", header = TRUE, sep=",")
Comparison <- test$comparison
Size <- test$size
plot(Comparison~Size)
lines(loess(test$comparison~test$size), col="black")
text(x=30,y=85,"LINKED LIST", family="serif")
