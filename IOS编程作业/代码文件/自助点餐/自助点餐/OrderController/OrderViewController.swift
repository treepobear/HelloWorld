//
//  OrderViewController.swift
//  自助点餐
//
//  Created by 蒋沁月 on 2020/5/19.
//  Copyright © 2020 BuffetOrder. All rights reserved.
//

import UIKit
import SQLite

class OrderViewController: UIViewController,UITableViewDelegate, UITableViewDataSource {

    var orderDicArray = Array<Any>()
    
    @IBOutlet weak var orderTableView: UITableView!
    @IBOutlet weak var okButton: UIButton!
    
    override func viewWillAppear(_ animated: Bool) {
        //初始化数据库
        var database: Database_Order!
        database = Database_Order()
        database.tableOrderCreate()
        orderDicArray = database.queryTableOrder()
        //订单button状态判断
        orderType()
        //刷新列表数据
        orderTableView.reloadData()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        orderTableView.delegate = self
        orderTableView.dataSource = self
        orderTableView.tableFooterView = UIView()       //隐藏多余空白cell
        orderTableView!.register(UINib(nibName:"OrderCell", bundle:nil),forCellReuseIdentifier:"OrderCell")     //加载cell
    }

    //tableView代理和数据源方法
    func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 1;
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return orderDicArray.count
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        80
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell: OrderCell = self.orderTableView.dequeueReusableCell(withIdentifier: "OrderCell") as! OrderCell
        cell.selectionStyle = .none
        let dic = orderDicArray[indexPath.row] as! Dictionary<String, Any>
        
        let dicJson = dic["dicArray"] as! String
        let dicArray = self.getArrayFromJSONString(jsonString: dicJson)
        
        var dishesName: String = ""
        for i in 0...dicArray.count-1 {
            let dic = dicArray[i] as! Dictionary<String,Any>
            dishesName += ", \(dic["dishes_Name"] as! String)"      //字符串拼接
        }
        dishesName.remove(at: dishesName.startIndex)        //删除第一个逗号
        cell.dishesLabel.text = dishesName
        
        cell.dishesNumber.text = "共 \(dicArray.count) 件"
        
        cell.restImageView.image = UIImage(named: dic["name"] as! String)
        cell.restNameLabel.text = (dic["name"] as! String)
        return cell
    }

      //设置哪些行可以编辑
    func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        return true
      }
      
      // 设置单元格的编辑的样式
      func tableView(_ tableView: UITableView, editingStyleForRowAt indexPath: IndexPath) -> UITableViewCell.EditingStyle {
          return UITableViewCell.EditingStyle.delete
      }
      
      //设置点击删除之后的操作
      func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCell.EditingStyle, forRowAt indexPath: IndexPath) {
          if editingStyle == .delete {
            var database: Database_Order!
            database = Database_Order()
            //根据订单id删除数据库指定数据
            let dic = self.orderDicArray[indexPath.row] as! Dictionary<String, Any>
            database.tableOrderDeleteItem(id: dic["id"] as! Int64)
            self.orderDicArray.remove(at: indexPath.row)
            if indexPath.row == 0 && indexPath.section == 0 {
                DispatchQueue.main.async(execute: {
                    self.orderTableView.reloadData()
                })
            }else{
                //刷新指定行
                tableView.deleteRows(at: [indexPath], with: UITableView.RowAnimation.automatic)
                tableView.reloadRows(at: [IndexPath(row: indexPath.row, section: indexPath.section)], with: .fade)
            }
            
          } else if editingStyle == .insert {
              
          }
        orderType()
      }
    
    //确认订单点击事件
    @IBAction func okButton(_ sender: Any) {
    
        let alertController = UIAlertController(title: "提示", message: "订单已选中,是否现在下单？", preferredStyle: .alert)
        let cancelAction = UIAlertAction(title: "取消", style: .cancel, handler: nil)
        let okAction = UIAlertAction(title: "好的", style: .default, handler: {
            action in
            print("点击了确定")
            let messageStr = "确认成功,请等待配送"
            let alertMessageController = UIAlertController(title: messageStr, message: nil, preferredStyle: .alert)
            //显示提示框
            self.present(alertMessageController, animated: true, completion: nil)
            //指定时间1.5秒后自动消失
            DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 2) {
                self.presentedViewController?.dismiss(animated: false, completion: nil)
                self.navigationController?.popViewController(animated: true)
            }
        })
        alertController.addAction(cancelAction)
        alertController.addAction(okAction)
        self.present(alertController, animated: true, completion: nil)
    }
    
    //订单button状态判断
    func orderType() {
        if orderDicArray.count > 0 {
            okButton.setTitle("确认订单", for: .normal)
            okButton.isEnabled = true
            okButton.backgroundColor = UIColor(red: 51/255, green: 199/255, blue: 89/255, alpha: 1)
        }else{
            okButton.setTitle("暂无订单", for: .normal)
            okButton.isEnabled = false
            okButton.backgroundColor = UIColor(red: 51/255, green: 199/255, blue: 89/255, alpha: 0.5)
        }
    }
    
    //json转数组
    func getArrayFromJSONString(jsonString:String) ->NSArray{
         
        let jsonData:Data = jsonString.data(using: .utf8)!
         
        let array = try? JSONSerialization.jsonObject(with: jsonData, options: .mutableContainers)
        if array != nil {
            return array as! NSArray
        }
        return array as! NSArray
         
    }
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
