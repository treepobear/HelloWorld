//
//  RestaurantViewController.swift
//  自助点餐
//
//  Created by 蒋沁月 on 2020/5/19.
//  Copyright © 2020 BuffetOrder. All rights reserved.
//

import UIKit
import SQLite
struct Database {
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
    // ============== 餐厅 ===============
    let TABLE_REST = Table("table_Rest") // 表名称
    let TABLE_REST_ID = Expression<Int64>("rest_id") // 列表项及项类型
    let TABLE_REST_NAME = Expression<String>("rest_name")
// 建表
    func tableRestCreate() -> Void {
        do {
            // 创建表TABLE_REST
        try db.run(TABLE_REST.create { table in
            table.column(TABLE_REST_ID, primaryKey: .autoincrement) // 主键自加且不为空
            table.column(TABLE_REST_NAME)
        })
        print("创建表 TABLE_REST 成功")
    } catch {
        print("创建表 TABLE_REST 失败：\(error)")
        }
    }
// 插入
    func tableRestInsertItem(name: String) -> Void {
        let insert = TABLE_REST.insert(TABLE_REST_NAME <- name)
        do {
            let rowid = try db.run(insert)
            print("插入数据成功 id: \(rowid)")
        } catch {
            print("插入数据失败: \(error)")
        }
    }
// 遍历
    func queryTableRest() -> Void {
        for item in (try! db.prepare(TABLE_REST)) {
            print("餐厅 遍历 ———— id: \(item[TABLE_REST_ID]), name: \(item[TABLE_REST_NAME])")
        }
    }
// 读取
    func readTableRestItem(id: Int64) -> NSDictionary {
        var dic = [String:Any]()
        for item in try! db.prepare(TABLE_REST.filter(TABLE_REST_ID == id)) {
            print("\n读取（餐厅）id: \(item[TABLE_REST_ID]), name: \(item[TABLE_REST_NAME])")
            dic = stringValueDic(item[TABLE_REST_NAME])!
        }
        return dic as NSDictionary
    }
    
    //字符串转字典
    func stringValueDic(_ str: String) -> [String : Any]?{
        let data = str.data(using: String.Encoding.utf8)
        if let dict = try? JSONSerialization.jsonObject(with: data!, options: JSONSerialization.ReadingOptions.mutableContainers) as? [String : Any] {
            return dict
        }
        return nil
    }
}

class RestaurantViewController: UIViewController,UITableViewDelegate,UITableViewDataSource {
    
    var restArray: Array<Dictionary<String, Any>> = []
    
    @IBOutlet weak var restaurantTableView: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.title = "餐厅"
        
        restaurantTableView.delegate = self
        restaurantTableView.dataSource = self
        restaurantTableView.tableFooterView = UIView()
        restaurantTableView!.register(UINib(nibName:"RestaurantCell", bundle:nil),forCellReuseIdentifier:"RestaurantCell")
        
        initData()
    }

    //初始化数据
    func initData() {
        // 与数据库建立连接
        var database: Database!
        database = Database()
        // 建立列表（有列表后不再建立）
        database.tableRestCreate()
        
        //创建模拟数据
        let rest1 = ["name":"吴家花园", "image":"吴家花园", "dishes":[["dishes_Name":"牛排","dishes_Image":"牛排","dishes_Details":"牛排，块状的牛肉。随着使用牛只部位的变更，延伸出多种不同的种类，是西餐中最常见的食物之一。牛排的烹调方法以煎和烧烤为主。","dishes_Price":"66"],["dishes_Name":"披萨","dishes_Image":"披萨","dishes_Details":"匹萨是一种著名的意大利食物。在中国大陆、台湾、新加坡以及马来西亚都是使用音译，其中pizza的pi写成“匹、披、比”都是通用的、只是各种音译的不同。在港澳通常直称Pizza或简称薄饼。","dishes_Price":"77"],["dishes_Name":"海鲜","dishes_Image":"海鲜","dishes_Details":"海鲜又称海产、海味，是指海洋中可食用的生物，大部分海鲜属于鱼类、甲壳类、软体动物或棘皮动物。虽然海带、海藻等海洋植物也是常用来烹饪美食的食材，但是海鲜主要还是指海产动物。","dishes_Price":"88"]]] as [String : Any]
        
        let rest2 = ["name":"知米鱼", "image":"知米鱼", "dishes":[["dishes_Name":"牛排","dishes_Image":"牛排","dishes_Details":"牛排，块状的牛肉。随着使用牛只部位的变更，延伸出多种不同的种类，是西餐中最常见的食物之一。牛排的烹调方法以煎和烧烤为主。","dishes_Price":"66"],["dishes_Name":"披萨","dishes_Image":"披萨","dishes_Details":"匹萨是一种著名的意大利食物。在中国大陆、台湾、新加坡以及马来西亚都是使用音译，其中pizza的pi写成“匹、披、比”都是通用的、只是各种音译的不同。在港澳通常直称Pizza或简称薄饼。","dishes_Price":"77"],["dishes_Name":"海鲜","dishes_Image":"海鲜","dishes_Details":"海鲜又称海产、海味，是指海洋中可食用的生物，大部分海鲜属于鱼类、甲壳类、软体动物或棘皮动物。虽然海带、海藻等海洋植物也是常用来烹饪美食的食材，但是海鲜主要还是指海产动物。","dishes_Price":"88"]]] as [String : Any]
        
        let rest3 = ["name":"食堂", "image":"食堂", "dishes":[["dishes_Name":"牛排","dishes_Image":"牛排","dishes_Details":"牛排，块状的牛肉。随着使用牛只部位的变更，延伸出多种不同的种类，是西餐中最常见的食物之一。牛排的烹调方法以煎和烧烤为主。","dishes_Price":"66"],["dishes_Name":"披萨","dishes_Image":"披萨","dishes_Details":"匹萨是一种著名的意大利食物。在中国大陆、台湾、新加坡以及马来西亚都是使用音译，其中pizza的pi写成“匹、披、比”都是通用的、只是各种音译的不同。在港澳通常直称Pizza或简称薄饼。","dishes_Price":"77"],["dishes_Name":"海鲜","dishes_Image":"海鲜","dishes_Details":"海鲜又称海产、海味，是指海洋中可食用的生物，大部分海鲜属于鱼类、甲壳类、软体动物或棘皮动物。虽然海带、海藻等海洋植物也是常用来烹饪美食的食材，但是海鲜主要还是指海产动物。","dishes_Price":"88"]]] as [String : Any]
        
        restArray = [rest1, rest2, rest3]
        
        //判断数据库内容是否为空 为空则添加数据 避免重复添加
        let dic = database.readTableRestItem(id: Int64(1)) as! [String:Any]
        if dic.isEmpty {
            for dic in restArray {
                database.tableRestInsertItem(name: dicValueString(dic)!)
            }
            database.queryTableRest()
        }
    }
    
    //tableView代理和数据源方法
    func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 1;
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return restArray.count
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        64
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell: RestaurantCell = self.restaurantTableView.dequeueReusableCell(withIdentifier: "RestaurantCell") as! RestaurantCell
        cell.selectionStyle = .none
        let dic = restArray[indexPath.row]
        cell.res_image.image = UIImage(named: dic["image"] as! String)
        cell.res_label.text = (dic["name"] as! String)
        return cell
    }
    
    //cell点击事件
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        var database: Database!
        database = Database()
        let dic = database.readTableRestItem(id: Int64(indexPath.row+1))
        //加载餐厅详情控制器
        let vc = RestDetailsViewController(nibName: "RestDetailsViewController", bundle: nil)
        vc.restDic = dic as! [String : Any]
        navigationController?.pushViewController(vc, animated: true)
    }

    //字典转字符串
    func dicValueString(_ dic:[String : Any]) -> String?{
        let data = try? JSONSerialization.data(withJSONObject: dic, options: [])
        let str = String(data: data!, encoding: String.Encoding.utf8)
        return str
    }
    
    //字符串转字典
    func stringValueDic(_ str: String) -> [String : Any]?{
        let data = str.data(using: String.Encoding.utf8)
        if let dict = try? JSONSerialization.jsonObject(with: data!, options: JSONSerialization.ReadingOptions.mutableContainers) as? [String : Any] {
            return dict
        }
        return nil
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
