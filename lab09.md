# “自顶向下，逐步求精”的编程方法：
## 百度上的说法：
>* 自顶向下的程序设计方法指的是首先从主控程序开始，然后按接口关系逐次分割每个功能为更小的功能模块，直到最低层模块设计完成为止。自顶向下是一种有序的逐步分层分解和求精的程序设计方法。其特点是层次清楚，编写方便，调试容易。(摘自百度词条)


## 维基上的说法：


>* A top-down approach (also known as stepwise design and in some cases used as a synonym of decomposition) is essentially the breaking down of a system to gain insight into its compositional sub-systems in a reverse engineering fashion. In a top-down approach an overview of the system is formulated, specifying, but not detailing, any first-level subsystems. Each subsystem is then refined in yet greater detail, sometimes in many additional subsystem levels, until the entire specification is reduced to base elements. A top-down model is often specified with the assistance of "black boxes", which makes it easier to manipulate. However, black boxes may fail to clarify elementary mechanisms or be detailed enough to realistically validate the model. Top down approach starts with the big picture. It breaks down from there into smaller segments.

## 本人看法：
* 自顶向下：是指按问题解决的顺序，将一个大问题分解为多个中问题，再将中问题分解为小问题，以此类推，将一个问题分解多个小问题；
* 逐步求精：是指将自顶向下步骤中分解成的小问题应用编程语言，将实例转化为具体的程序实现；具体转化方式有 
    * 顺序结构；
    * 循环结构；
    * 选择结构；



# 洗衣机控制程序设计：
        
        READ (water_height,soak_time,wash_time,rush_time)//读取预设水位，浸泡时间，漂洗时间，脱水时间；
        WHILE(height<water_height){
                repeat
                water_in_swicth(open)
        }
        water_in_swicth(close)
        ENDWHILE
        WHILE(soak_time>0){
                repeat
                soak_time--//浸泡时间减少；
        }
        ENDWHILE
        WHILE(wash_time>0){
                repeat
                FOR i=1 to 3
                        motor_run(left)//转机左转三圈；
                ENDFOR
                FOR i=1 to 3
                        motor_run(right)//转机右转三圈；
                ENDFOR
                wash_time--//漂洗时间减少；
        }
        ENDWHILE
        motor(stop)//转机停止；
        WHILE(water_height>0){
                repeat
                water_out_swicth(open)
        }
        ENDWHILE
        water_out_swicth(close)
        WHILE(rush_time>0){
                repeat
                motor(open)
                rush_time--//脱水时间减少；
        }
        ENDWHILE
        motor(close)
        halt(success) 
        