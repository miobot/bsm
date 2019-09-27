# frozen_string_literal: true

require 'bsm/bsm_parse/internal'

module Bsm
  # Parser module, wraps the native functions with some error handling
  module BsmParse
    def self.runtest(hello)
      bsm_parse_test(hello)
    end

    def self.compile_to_ast(string)
      return bsm_parse_compile_to_ast(string) if string.is_a? String

      raise 'Invalid type given. This method only accepts strings'
    end
  end
end
