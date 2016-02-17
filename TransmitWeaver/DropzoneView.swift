//
//  DropzoneView.swift
//  TransmitWeaver
//
//  Created by Stephen Radford on 16/02/2016.
//  Copyright © 2016 Cocoon Development Ltd. All rights reserved.
//

import Cocoa

protocol DropzoneDelegate: class {
    
    func dragStart()
    
    func dragEnd()
    
    func dragCompleted(path: String)
    
}

class DropzoneView: NSView {
    
    weak var delegate: DropzoneDelegate?
    
    var filePath: String?
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
        let types = [NSURLPboardType]
        registerForDraggedTypes(types)
    }
    
    override func draggingEntered(sender: NSDraggingInfo) -> NSDragOperation  {
        
        filePath = nil
        
        if let filenames = sender.draggingPasteboard().propertyListForType(NSFilenamesPboardType) {
            if filenames.count > 0 {
                let path = filenames[0]
                if path.pathExtension == "ste" {
                    delegate?.dragStart()
                    filePath = path as? String
                    return NSDragOperation.Generic
                }
            }
        }
        
        return NSDragOperation.None
    }
    
    override func performDragOperation(sender: NSDraggingInfo) -> Bool {
        delegate?.dragEnd()
        
        if let path = filePath {
            delegate?.dragCompleted(path)
        }
        
        return true
    }
    
    override func draggingExited(sender: NSDraggingInfo?) {
        delegate?.dragEnd()
    }
    
    
}
