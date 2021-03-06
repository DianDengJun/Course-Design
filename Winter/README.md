# 2021年寒假实训项目

## [项目一 迷宫求解](./Project1/)
以一个 m × n 的长方阵表示迷宫，0 和 1 分别表示迷宫中的通路和障碍。设计一个程序，
对任意设定的迷宫，求出一条从入口到出口的通路，或得出没有通路的结论。

## [项目二 停车场管理系统](./Project2/)
停车场内只有一个可停放 n 辆汽车的狭长通道，且只有一个大门可供汽车进出。

汽车在停车场内按车辆到达时间的先后顺序，依次由北向南排列（大门在最南端，最先到
达的第一辆车停放在停车场的最北端），若车场内已停满 n 辆汽车，则后来的汽车只能在门外
的便道上等候，一旦有车开走，则排在便道上的第一辆车即可开入。

当停车场内某辆车要离开时，在它之后开入的车辆必须先退出车场为它让路，待该辆车开
出大门外，其它车辆再按原次序进入车场，每辆停放在车场的车在它离开车场时必须按它停留
的时间长短交纳费用。

试为停车场编制按上述要求进行管理的模拟程序。

## [项目三 哈夫曼编（译）码系统](./Project3)
利用哈夫曼编码进行通信可以大大提高信道利用率，缩短信息传输时间，降低传输成本。
但是，这要求在发送端通过一个编码系统对待传数据预先编码，在接收端将传来的数据进行译码（解码）。
对于双工信道（即可以双向传输信息的信道），每端都需要一个完整的编/译码系统。
试为这样的信息收发站设计一个哈夫曼编译码系统。