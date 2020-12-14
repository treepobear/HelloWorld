//
//  DisheesDetailsViewController.swift
//  自助点餐
//
//  Created by 蒋沁月 on 2020/5/22.
//  Copyright © 2020 BuffetOrder. All rights reserved.
//

import UIKit
import SQLite

struct Database_Order {
    var db: Connection!
    
    init() {
        connectDatabase()
    }
    mutating func connectDatabase(filePath: String = "/Documents") -> Void {
        let sqlFilePath = NSHomeDirectory() + filePath + "/db.sqlite3"
        do {
            // 与数据库建立连接
            db = try Connection(sqlFilePath)
            print("与数据库建立连接 成功")
        } catch {
            print("与数据库建立连接 失败：\(error)")
        }
    }
    // ============== 订单 ===============
    let TABLE_ORDER = Table("table_Order") // 表名称
    let TABLE_ORDER_ID = Expression<Int64>("rest_id") // 列表项及项类型
    let TABLE_ORDER_NAME = Expression<String>("rorder_name")
    let TABLE_ORDER_DICTARRAY = Expression<String>("order_dicArray")
// 建表
    func tableOrderCreate() -> Void {
        do {
            // 创建表TABLE_ORDER
        try db.run(TABLE_ORDER.create { table in
            table.column(TABLE_ORDER_ID, primaryKey: .autoincrement) // 主键自加且不为空
            table.column(TABLE_ORDER_NAME)
            table.column(TABLE_ORDER_DICTARRAY)
        })
        print("创建表 TABLE_REST 成功")
    } catch {
        print("创建表 TABLE_REST 失败：\(error)")
        }
    }
// 插入
    func tableRestInsertItem(name: String, ordeDicArray: String) -> Void {
        //字典数组转string 因为数据库无法直接存储数组格式数据
        let insert = TABLE_ORDER.insert(TABLE_ORDER_NAME <- name, TABLE_ORDER_DICTARRAY <- ordeDicArray)
        do {
            let rowid = try db.run(insert)
            print("插入数据成功 id: \(rowid)")
        } catch {
            print("插入数据失败: \(error)")
        }
    }
// 读取
    func readTableOrderName(orderName: String) -> NSDictionary {
        var dic = [String:Any]()
        for item in try! db.prepare(TABLE_ORDER.filter(TABLE_ORDER_NAME == orderName)) {
            print("\n读取（餐厅）id: \(item[TABLE_ORDER_ID]), name: \(item[TABLE_ORDER_NAME])")
            dic = ["orderDicArray":item[TABLE_ORDER_DICTARRAY]]
        }
        return dic as NSDictionary
    }
// 更新
    func tableOrderUpdateItem(name: String, orderDicArray: String) -> Void {
        let item = TABLE_ORDER.filter(TABLE_ORDER_NAME == name)
        do {
            if try db.run(item.update(TABLE_ORDER_DICTARRAY <- orderDicArray)) > 0 {
                print("订单\(orderDicArray) 更新成功")
            } else {
                print("没有发现 订单条目 \(orderDicArray)")
            }
        } catch {
            print("订单\(orderDicArray) 更新失败：\(error)")
        }
    }
    // 遍历
    func queryTableOrder() -> Array<Any> {
        var orderDicArray = Array<Dictionary<String, Any>>()
        for item in (try! db.prepare(TABLE_ORDER)) {
            print("订单 遍历 ———— id: \(item[TABLE_ORDER_ID]), name: \(item[TABLE_ORDER_NAME]), dicArray: \(item[TABLE_ORDER_DICTARRAY])")
            let dic = ["id": item[TABLE_ORDER_ID], "name":item[TABLE_ORDER_NAME], "dicArray":item[TABLE_ORDER_DICTARRAY]] as [String : Any]
            orderDicArray.append(dic)
        }
        return orderDicArray
    }
    // 删除
    func tableOrderDeleteItem(id: Int64) -> Void {
        let item = TABLE_ORDER.filter(TABLE_ORDER_ID == id)
        do {
            if try db.run(item.delete()) > 0 {
                print("餐厅\(id) 删除成功")
            } else {
                print("没有发现 餐厅条目 \(id)") }
        } catch {
            print("餐厅\(id) 删除失败：\(error)")
        }
    }
}

class DisheesDetailsViewController: UIViewController {

    @IBOutlet weak var dishesImage: UIImageView!
    @IBOutlet weak var dishesName: UILabel!
    @IBOutlet weak var dishesPrice: UILabel!
    @IBOutlet weak var textFile: UITextView!
    
    
    var dishes_Dic = [String:Any]()
    var database: Database_Order!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // 与数据库建立连接
        self.database = Database_Order()
        // 建立列表（有列表后不再建立）
        self.database.tableOrderCreate()
        
        title = (dishes_Dic["dishes_Name"] as? String)!
        dishesImage.image = UIImage(named: dishes_Dic["dishes_Image"] as! String)
        dishesName.text = dishes_Dic["dishes_Name"] as? String
        dishesPrice.text = "¥ \(dishes_Dic["dishes_Price"] as! String)"
        textFile.text = dishes_Dic["dishes_Details"] as? String
    }

    
    @IBAction func addDishesButtonTouch(_ sender: Any) {
        let actionSheet = UIAlertController.init(title: nil, message: nil, preferredStyle: .actionSheet)
        let title = "提示"
        let titleStr = NSMutableAttributedString.init(string: title)
        titleStr.addAttribute(NSAttributedString.Key.foregroundColor, value: UIColor.orange, range: NSRange.init(location: 0, length: title.count))
        titleStr.addAttribute(NSAttributedString.Key.font, value: UIFont.systemFont(ofSize:20), range: NSRange.init(location: 0, length: title.count))
        actionSheet.setValue(titleStr, forKey: "attributedTitle")
        
        let message = "添加后可在订单界面查看相关信息"
        let messageStr = NSMutableAttributedString.init(string: message)
        messageStr.addAttribute(NSAttributedString.Key.foregroundColor, value: UIColor.orange, range: NSRange.init(location: 0, length: message.count))
        messageStr.addAttribute(NSAttributedString.Key.font, value: UIFont.systemFont(ofSize:17), range: NSRange.init(location: 0, length: message.count))
        actionSheet.setValue(messageStr, forKey: "attributedMessage")
        
        let cancelAction = UIAlertAction.init(title: "取消", style: .cancel) { (action) in
            
        }
        
        let action = UIAlertAction.init(title: "好的", style: .default) { (action) in
            var orderDicArray = Array<Dictionary<String,Any>>()
            let restName = UserDefaults.standard.string(forKey: "rest_name")
            let oldDic = self.database.readTableOrderName(orderName: restName!) as! [String:Any]
            print(oldDic)
            if oldDic.isEmpty {
                orderDicArray.append(self.dishes_Dic)
                let result = self.getJSONStringFromArray(array: orderDicArray as NSArray)
                self.database.tableRestInsertItem(name: restName!, ordeDicArray: result as String)
            }else{
                orderDicArray = self.getArrayFromJSONString(jsonString: oldDic["orderDicArray"] as! String) as! [Dictionary<String, Any>]
                print(orderDicArray)
                orderDicArray.append(self.dishes_Dic)
                let result = self.getJSONStringFromArray(array: orderDicArray as NSArray)
                self.database.tableOrderUpdateItem(name: restName!, orderDicArray: result)
            }
            
            let orderArray = self.database.queryTableOrder()
            print(orderArray)
            
            let alertController = UIAlertController(title: "下单成功!", message: nil, preferredStyle: .alert)
            //显示提示框
            self.present(alertController, animated: true, completion: nil)
            //指定时间1.5秒后自动消失
            DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 1.5) {
                self.presentedViewController?.dismiss(animated: false, completion: nil)
                self.navigationController?.popViewController(animated: true)
            }
        }
        actionSheet.addAction(cancelAction)
        actionSheet.addAction(action)
        UIApplication.shared.keyWindow?.rootViewController?.present(actionSheet, animated: true, completion: { })
    }
    
    //数组转json
    func getJSONStringFromArray(array:NSArray) -> String {
         
        if (!JSONSerialization.isValidJSONObject(array)) {
            print("无法解析出JSONString")
            return ""
        }
         
        let data = try? JSONSerialization.data(withJSONObject: array, options: JSONSerialization.WritingOptions.prettyPrinted)
        let strJson = NSString(data: data!, encoding: String.Encoding.utf8.rawValue)
        return strJson! as String
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
