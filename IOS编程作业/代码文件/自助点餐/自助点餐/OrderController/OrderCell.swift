//
//  OrderCell.swift
//  自助点餐
//
//  Created by 蒋沁月 on 2020/5/22.
//  Copyright © 2020 BuffetOrder. All rights reserved.
//

import UIKit

class OrderCell: UITableViewCell {

    @IBOutlet weak var restImageView: UIImageView!
    @IBOutlet weak var restNameLabel: UILabel!
    @IBOutlet weak var dishesLabel: UILabel!
    @IBOutlet weak var dishesNumber: UILabel!
    
    
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
}
