//
//  RestDetailsViewController.swift
//  自助点餐
//
//  Created by 蒋沁月 on 2020/5/21.
//  Copyright © 2020 BuffetOrder. All rights reserved.
//

import UIKit

class RestDetailsViewController: UIViewController,UITableViewDelegate,UITableViewDataSource {

    @IBOutlet weak var restDetailsTableView: UITableView!
    var restDic = [String:Any]()
    var detailsArraay: Array<Dictionary<String,Any>> = []
    
    override func viewDidLoad() {
        super.viewDidLoad()

        title = (restDic["name"] as! String)
        UserDefaults().set((restDic["name"] as! String), forKey: "rest_name")
        
        detailsArraay = restDic["dishes"] as! Array<Dictionary<String, Any>>
        
        restDetailsTableView.delegate = self
        restDetailsTableView.dataSource = self
        restDetailsTableView.tableFooterView = UIView()
        restDetailsTableView!.register(UINib(nibName:"RestaurantCell", bundle:nil),forCellReuseIdentifier:"RestaurantCell")
    }

    func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 1;
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return detailsArraay.count
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        64
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell: RestaurantCell = self.restDetailsTableView.dequeueReusableCell(withIdentifier: "RestaurantCell") as! RestaurantCell
        cell.selectionStyle = .none
        let dic = detailsArraay[indexPath.row]
        cell.res_image.image = UIImage(named: dic["dishes_Image"] as! String)
        cell.res_label.text = (dic["dishes_Name"] as! String)
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let dic = detailsArraay[indexPath.row]
        let vc = DisheesDetailsViewController(nibName: "DisheesDetailsViewController", bundle: nil)
        vc.dishes_Dic = dic
        navigationController?.pushViewController(vc, animated: true)
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
