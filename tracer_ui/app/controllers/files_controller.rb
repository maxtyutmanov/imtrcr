class FilesController < ApplicationController
  def index
    #renders the view
  end
  
  def upload
    uploaded_io = params[:upload]
    
    client = Savon::Client.new do |wsdl, http|
      wsdl.document = File.expand_path("../../../imtrcr_soap.wsdl", __FILE__)
    end
    
    tracing_result = client.request :trace do 
      soap.body = { :imageData => Base64.encode64(uploaded_io.read) }
    end
    
    if tracing_result.body[:trace_response][:status_code] == "0"
      #debugger
    
      tmp_file_path = Rails.root.join('public', 'uploads', 'traced') #uploaded_io.original_filename)
      
      svg = tracing_result.body[:trace_response][:svg_xml]
      doc = Nokogiri::XML.parse(svg)
      
      
      File.open(tmp_file_path, 'w') do |file|
        file.write(doc.to_s)
      end
    
      send_file tmp_file_path, :type => "image/svg+xml"
    else
      redirect_to :action => :index
    end
#    File.open(Rails.root.join('public', 'uploads', uploaded_io.original_filename), 'w') do |file|#
#      file.write(Base64.encode64(uploaded_io.read))
#    end
  end
end
