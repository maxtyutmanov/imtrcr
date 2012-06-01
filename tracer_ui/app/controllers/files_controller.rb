class FilesController < ApplicationController
  def index
    #renders the view
  end
  
  def upload
    angularity = params[:settings][:angularity]
    
    if !(angularity =~ /^\d+$/)
      flash[:warning] = 'Error: please specify angularity correctly. It has to be integer'
      return redirect_to :action => :index
    end
    
    if (Integer(angularity) < 0 or Integer(angularity) > 100)
      flash[:warning] = 'Error: angularity must be in range from 0 to 100'
      return redirect_to :action => :index
    end
    
    despeckling = params[:settings][:despeckling]
    
    if !(despeckling =~ /^\d+$/) || Integer(despeckling) < 0
      flash[:warning] = 'Error: please specify despeckling correctly. It has to be nonnegative integer'
      return redirect_to :action => :index
    end
       
    uploaded_io = params[:upload]
    
    if (uploaded_io == nil)
      flash[:warning] = 'Upload some file, otherwise we have nothing to vectorize!'
      return redirect_to :action => :index
    end
    
    client = Savon::Client.new do |wsdl, http|
      wsdl.document = File.expand_path("../../../imtrcr_soap.wsdl", __FILE__)
    end
    
    tracing_result = client.request :trace do 
      soap.body = 
      { 
        :authToken => 'BD04130C-AC30-11E1-ACA8-95196288709B',
        :imageData => Base64.encode64(uploaded_io.read),
        :despecklingPixels => despeckling,
        :angularity => angularity
      }
    end
    
    status_code = tracing_result.body[:trace_response][:status_code]
    
    if status_code == '200'
      tmp_file_path = Rails.root.join('public', 'uploads', 'traced')
      
      svg = tracing_result.body[:trace_response][:svg_xml]
      doc = Nokogiri::XML.parse(svg)
      
      
      File.open(tmp_file_path, 'w') do |file|
        file.write(doc.to_s)
      end
    
      send_file tmp_file_path, :type => "image/svg+xml"
    else
      if status_code == '400'
        flash[:warning] = 'Error: wrong image file format'
      else
        flash[:warning] = 'Service is temporary unavailable. Please try later. Sorry for inconvenience.'
      end
        
      redirect_to :action => :index
    end
  end
end
